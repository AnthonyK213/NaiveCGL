#include <naivecgl/Geometry/HalfEdgeMesh.h>

#include <tuple>

Naive_Namespace_Begin(geometry);

HalfEdgeMesh::Vertex::Vertex() {}

HalfEdgeMesh::Vertex::Vertex(const Naive_Vector3d &coord)
    : m_coord(coord), m_edge(nullptr), m_id(0) {}

HalfEdgeMesh::Vertex::Vertex(Naive_Real x, Naive_Real y, Naive_Real z)
    : m_coord(x, y, z), m_edge(nullptr), m_id(0) {}

HalfEdgeMesh::Vertex::Vertex(Vertex &&other) noexcept {
  m_coord = std::move(other.m_coord);
  m_edge = other.m_edge;
  other.m_edge = nullptr;
  m_id = other.m_id;
}

HalfEdgeMesh::Vertex &HalfEdgeMesh::Vertex::operator=(Vertex &&other) noexcept {
  m_coord = std::move(other.m_coord);
  m_edge = other.m_edge;
  other.m_edge = nullptr;
  m_id = other.m_id;

  return *this;
}

HalfEdgeMesh::Vertex::~Vertex() {}

HalfEdgeMesh::HalfEdge::HalfEdge() {}

HalfEdgeMesh::HalfEdge::HalfEdge(Vertex *origin)
    : m_origin(origin), m_twin(nullptr), m_face(nullptr), m_next(nullptr),
      m_id(0) {}

HalfEdgeMesh::HalfEdge::HalfEdge(HalfEdge &&other) noexcept {
  m_origin = other.m_origin;
  m_twin = other.m_twin;
  m_face = other.m_face;
  m_next = other.m_next;
  other.m_origin = nullptr;
  other.m_twin = nullptr;
  other.m_face = nullptr;
  other.m_next = nullptr;
  m_id = other.m_id;
}

HalfEdgeMesh::HalfEdge &
HalfEdgeMesh::HalfEdge::operator=(HalfEdge &&other) noexcept {
  m_origin = other.m_origin;
  m_twin = other.m_twin;
  m_face = other.m_face;
  m_next = other.m_next;
  other.m_origin = nullptr;
  other.m_twin = nullptr;
  other.m_face = nullptr;
  other.m_next = nullptr;
  m_id = other.m_id;

  return *this;
}

HalfEdgeMesh::HalfEdge::~HalfEdge() {}

HalfEdgeMesh::Face::Face() {}

HalfEdgeMesh::Face::Face(HalfEdge *outerEdge)
    : m_outerEdge(outerEdge), m_normal(0., 0., 0.), m_id(0) {}

HalfEdgeMesh::Face::Face(Face &&other) noexcept {
  m_outerEdge = other.m_outerEdge;
  other.m_outerEdge = nullptr;
  m_normal = std::move(other.m_normal);
  m_id = other.m_id;
}

HalfEdgeMesh::Face &HalfEdgeMesh::Face::operator=(Face &&other) noexcept {
  m_outerEdge = other.m_outerEdge;
  other.m_outerEdge = nullptr;
  m_normal = std::move(other.m_normal);
  m_id = other.m_id;

  return *this;
}

HalfEdgeMesh::Face::~Face() {}

HalfEdgeMesh::Face::EdgeIterator::EdgeIterator(const Face *face) {
  m_owner = face;
  m_current = face->m_outerEdge;
  m_firstTime = true;
}

Naive_Bool HalfEdgeMesh::Face::EdgeIterator::more() const {
  if (m_current == nullptr) {
    return false;
  }

  if (m_firstTime) {
    m_firstTime = false;
    return true;
  }

  if (m_current == m_owner->m_outerEdge) {
    return false;
  }

  return true;
}

HalfEdgeMesh::HalfEdgeMesh()
    : m_vertexIndex(0), m_halfEdgeIndex(0), m_faceIndex(0) {}

HalfEdgeMesh::HalfEdgeMesh(const TriangleSoup &triangleSoup)
    : m_vertexIndex(0), m_halfEdgeIndex(0), m_faceIndex(0) {
  /// Insert vertices.
  for (const Naive_Vector3d &vertex : triangleSoup.vertices()) {
    addVertex({vertex});
  }

  /// Insert faces and their edges.
  /// Twins of the half-edges are not set yet.
  for (const Naive_Triangle &triangle : triangleSoup.triangles()) {
    /// Vertex key starts from 1!
    HalfEdge &edge0 = addHalfEdge({&m_vertices[triangle(0) + 1]});
    HalfEdge &edge1 = addHalfEdge({&m_vertices[triangle(1) + 1]});
    HalfEdge &edge2 = addHalfEdge({&m_vertices[triangle(2) + 1]});

    edge0.m_next = &edge1;
    edge1.m_next = &edge2;
    edge2.m_next = &edge0;

    /// TODO: Boundary check.
    edge0.m_origin->m_edge = &edge0;
    edge1.m_origin->m_edge = &edge1;
    edge2.m_origin->m_edge = &edge2;

    Face &face = addFace({&edge0});

    /// Store face index in the boundary edges.
    edge0.m_face = &face;
    edge1.m_face = &face;
    edge2.m_face = &face;
  }

  makeTwins();
}

HalfEdgeMesh::~HalfEdgeMesh() {}

HalfEdgeMesh::Vertex &HalfEdgeMesh::addVertex(Vertex &&vertex) {
  Naive_Integer id = ++m_vertexIndex;
  m_vertices.emplace(id, std::move(vertex));
  Vertex &vert = m_vertices[id];
  vert.m_id = id;
  return vert;
}

HalfEdgeMesh::HalfEdge &HalfEdgeMesh::addHalfEdge(HalfEdge &&halfEdge) {
  Naive_Integer id = ++m_halfEdgeIndex;
  m_halfEdges.emplace(id, std::move(halfEdge));
  HalfEdge &edge = m_halfEdges[id];
  edge.m_id = id;
  return edge;
}

HalfEdgeMesh::Face &HalfEdgeMesh::addFace(Face &&face) {
  Naive_Integer id = ++m_faceIndex;
  m_faces.emplace(id, std::move(face));
  Face &f = m_faces[id];
  f.m_id = id;
  return f;
}

void HalfEdgeMesh::makeTwins() {
  /// Use an ordered map to find "duplicate" edges.
  /// Better solution?

  Naive_Map<std::tuple<Naive_Integer, Naive_Integer>, Naive_Integer> edgeMap{};

  for (auto it = m_halfEdges.cbegin(); it != m_halfEdges.cend(); ++it) {
    Naive_Integer thisV = it->second.m_origin->m_id;
    Naive_Integer nextV = it->second.m_next->m_origin->m_id;

    /// The key is the index of the start and end vertex indices: (a, b),
    /// which a <= b.
    if (thisV > nextV)
      std::swap(thisV, nextV);

    std::tuple<Naive_Integer, Naive_Integer> tup{thisV, nextV};
    auto key = edgeMap.find(tup);

    /// If the edge is not in the `edgeMap`, just insert the pair.
    if (key == edgeMap.cend()) {
      edgeMap.emplace(tup, it->first);
      continue;
    }

    /// Finally find the "duplicate" edges, make them twins.
    HalfEdge *edge = &m_halfEdges[it->first];
    HalfEdge *theTwin = &m_halfEdges[key->second];
    theTwin->m_twin = edge;
    edge->m_twin = theTwin;
  }
}

Naive_Namespace_End(geometry);
