#include <naivecgl/Geometry/HalfEdgeMesh.h>

#include <tuple>

Naive_NAMESPACE_BEGIN(geometry);

HalfEdgeMesh::Vertex::Vertex() {}

HalfEdgeMesh::Vertex::Vertex(const Naive_Vector3d &theCoord)
    : myCoord(theCoord), myEdge(nullptr), myId(0) {}

HalfEdgeMesh::Vertex::Vertex(Naive_Real theX, Naive_Real theY,
                               Naive_Real theZ)
    : myCoord(theX, theY, theZ), myEdge(nullptr), myId(0) {}

HalfEdgeMesh::Vertex::Vertex(Vertex &&theOther) noexcept {
  myCoord = std::move(theOther.myCoord);
  myEdge = theOther.myEdge;
  theOther.myEdge = nullptr;
  myId = theOther.myId;
}

HalfEdgeMesh::Vertex &
HalfEdgeMesh::Vertex::operator=(Vertex &&theOther) noexcept {
  myCoord = std::move(theOther.myCoord);
  myEdge = theOther.myEdge;
  theOther.myEdge = nullptr;
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::Vertex::~Vertex() {}

HalfEdgeMesh::HalfEdge::HalfEdge() {}

HalfEdgeMesh::HalfEdge::HalfEdge(Vertex *theOrigin)
    : myOrigin(theOrigin), myTwin(nullptr), myFace(nullptr), myNext(nullptr),
      myId(0) {}

HalfEdgeMesh::HalfEdge::HalfEdge(HalfEdge &&theOther) noexcept {
  myOrigin = theOther.myOrigin;
  myTwin = theOther.myTwin;
  myFace = theOther.myFace;
  myNext = theOther.myNext;
  theOther.myOrigin = nullptr;
  theOther.myTwin = nullptr;
  theOther.myFace = nullptr;
  theOther.myNext = nullptr;
  myId = theOther.myId;
}

HalfEdgeMesh::HalfEdge &
HalfEdgeMesh::HalfEdge::operator=(HalfEdge &&theOther) noexcept {
  myOrigin = theOther.myOrigin;
  myTwin = theOther.myTwin;
  myFace = theOther.myFace;
  myNext = theOther.myNext;
  theOther.myOrigin = nullptr;
  theOther.myTwin = nullptr;
  theOther.myFace = nullptr;
  theOther.myNext = nullptr;
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::HalfEdge::~HalfEdge() {}

HalfEdgeMesh::Face::Face() {}

HalfEdgeMesh::Face::Face(HalfEdge *theOuterEdge)
    : myOuterEdge(theOuterEdge), myNormal(0., 0., 0.), myId(0) {}

HalfEdgeMesh::Face::Face(Face &&theOther) noexcept {
  myOuterEdge = theOther.myOuterEdge;
  theOther.myOuterEdge = nullptr;
  myNormal = std::move(theOther.myNormal);
  myId = theOther.myId;
}

HalfEdgeMesh::Face &HalfEdgeMesh::Face::operator=(Face &&theOther) noexcept {
  myOuterEdge = theOther.myOuterEdge;
  theOther.myOuterEdge = nullptr;
  myNormal = std::move(theOther.myNormal);
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::Face::~Face() {}

HalfEdgeMesh::Face::EdgeIterator::EdgeIterator(const Face *theFace) {
  myOwner = theFace;
  myCurrent = theFace->myOuterEdge;
  myFirstTime = true;
}

Naive_Bool HalfEdgeMesh::Face::EdgeIterator::More() const {
  if (myCurrent == nullptr) {
    return false;
  }

  if (myFirstTime) {
    myFirstTime = false;
    return true;
  }

  if (myCurrent == myOwner->myOuterEdge) {
    return false;
  }

  return true;
}

HalfEdgeMesh::HalfEdgeMesh()
    : myVertexIndex(0), myHalfEdgeIndex(0), myFaceIndex(0) {}

HalfEdgeMesh::HalfEdgeMesh(const TriangleSoup &theTriangleSoup)
    : myVertexIndex(0), myHalfEdgeIndex(0), myFaceIndex(0) {
  /// Insert vertices.
  for (const Naive_Vector3d &aVertex : theTriangleSoup.Vertices()) {
    addVertex({aVertex});
  }

  /// Insert faces and their edges.
  /// Twins of the half-edges are not set yet.
  for (const Naive_Triangle &aTriangle : theTriangleSoup.Triangles()) {
    /// Vertex key starts from 1!
    HalfEdge &edge0 = addHalfEdge({&myVertices[aTriangle(0) + 1]});
    HalfEdge &edge1 = addHalfEdge({&myVertices[aTriangle(1) + 1]});
    HalfEdge &edge2 = addHalfEdge({&myVertices[aTriangle(2) + 1]});

    edge0.myNext = &edge1;
    edge1.myNext = &edge2;
    edge2.myNext = &edge0;

    /// TODO: Boundary check.
    edge0.myOrigin->myEdge = &edge0;
    edge1.myOrigin->myEdge = &edge1;
    edge2.myOrigin->myEdge = &edge2;

    Face &face = addFace({&edge0});

    /// Store face index in the boundary edges.
    edge0.myFace = &face;
    edge1.myFace = &face;
    edge2.myFace = &face;
  }

  makeTwins();
}

HalfEdgeMesh::~HalfEdgeMesh() {}

HalfEdgeMesh::Vertex &HalfEdgeMesh::addVertex(Vertex &&theVertex) {
  Naive_Integer id = ++myVertexIndex;
  myVertices.emplace(id, std::move(theVertex));
  Vertex &vert = myVertices[id];
  vert.myId = id;
  return vert;
}

HalfEdgeMesh::HalfEdge &HalfEdgeMesh::addHalfEdge(HalfEdge &&theHalfEdge) {
  Naive_Integer id = ++myHalfEdgeIndex;
  myHalfEdges.emplace(id, std::move(theHalfEdge));
  HalfEdge &edge = myHalfEdges[id];
  edge.myId = id;
  return edge;
}

HalfEdgeMesh::Face &HalfEdgeMesh::addFace(Face &&theFace) {
  Naive_Integer id = ++myFaceIndex;
  myFaces.emplace(id, std::move(theFace));
  Face &f = myFaces[id];
  f.myId = id;
  return f;
}

void HalfEdgeMesh::makeTwins() {
  /// Use an ordered map to find "duplicate" edges.
  /// Better solution?

  Naive_Map<std::tuple<Naive_Integer, Naive_Integer>, Naive_Integer> edgeMap{};

  for (auto anIter = myHalfEdges.cbegin(); anIter != myHalfEdges.cend();
       ++anIter) {
    Naive_Integer thisV = anIter->second.myOrigin->myId;
    Naive_Integer nextV = anIter->second.myNext->myOrigin->myId;

    /// The key is the index of the start and end vertex indices: (a, b),
    /// which a <= b.
    if (thisV > nextV)
      std::swap(thisV, nextV);

    std::tuple<Naive_Integer, Naive_Integer> tup{thisV, nextV};
    auto key = edgeMap.find(tup);

    /// If the edge is not in the `edgeMap`, just insert the pair.
    if (key == edgeMap.cend()) {
      edgeMap.emplace(tup, anIter->first);
      continue;
    }

    /// Finally find the "duplicate" edges, make them twins.
    HalfEdge *edge = &myHalfEdges[anIter->first];
    HalfEdge *theTwin = &myHalfEdges[key->second];
    theTwin->myTwin = edge;
    edge->myTwin = theTwin;
  }
}

Naive_NAMESPACE_END(geometry);
