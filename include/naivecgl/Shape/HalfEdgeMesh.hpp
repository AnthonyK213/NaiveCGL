#ifndef NAIVECGL_SHAPE_HALF_EDGE_MESH_H
#define NAIVECGL_SHAPE_HALF_EDGE_MESH_H

#include "TriangleSoup.hpp"

#include <tuple>

namespace naivecgl {
namespace shape {

/// @brief Manifold mesh described by half-edges.
/// @tparam FloatType
/// @tparam IndexType

template <typename FloatType, typename IndexType> class HalfEdgeMesh {
public:
  class Vertex;
  class HalfEdge;
  class Face;

  class Vertex {
    friend class HalfEdgeMesh;

  public:
    Vertex() {}

    Vertex(const Eigen::Vector3<FloatType> &coord)
        : m_coord(coord), m_edge(nullptr), m_id(0) {}

    Vertex(FloatType x, FloatType y, FloatType z)
        : m_coord(x, y, z), m_edge(nullptr), m_id(0) {}

    Vertex(const Vertex &other) = delete;

    Vertex(Vertex &&other) noexcept {
      m_coord = std::move(other.m_coord);
      m_edge = other.m_edge;
      other.m_edge = nullptr;
      m_id = other.m_id;
    }

    Vertex &operator=(const Vertex &other) = delete;

    Vertex &operator=(Vertex &&other) noexcept {
      m_coord = std::move(other.m_coord);
      m_edge = other.m_edge;
      other.m_edge = nullptr;
      m_id = other.m_id;
    }

    ~Vertex() {}

  public:
    const Eigen::Vector3<FloatType> &coordinates() const { return m_coord; }

    Eigen::Vector3<FloatType> &coordinatesMut() { return m_coord; }

    IndexType id() const { return m_id; }

  private:
    Eigen::Vector3<FloatType> m_coord; // Vertex coordinates.
    HalfEdge *m_edge;                  // An half-edge starts with the vertex.
    IndexType m_id;                    // The ID(key) in the vertex map.
  };

  class HalfEdge {
    friend class HalfEdgeMesh;

  public:
    HalfEdge() {}

    HalfEdge(Vertex *origin)
        : m_origin(origin), m_twin(nullptr), m_face(nullptr), m_next(nullptr),
          m_id(0) {}

    HalfEdge(const HalfEdge &other) = delete;

    HalfEdge(HalfEdge &&other) noexcept {
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

    HalfEdge &operator=(const HalfEdge &other) = delete;

    HalfEdge &operator=(HalfEdge &&other) noexcept {
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

    ~HalfEdge() {}

  public:
    const Vertex *origin() const { return m_origin; }

    const HalfEdge *twin() const { return m_twin; }

    const Face *face() const { return m_face; }

    const HalfEdge *next() const { return m_next; }

    IndexType id() const { return m_id; }

  private:
    Vertex *m_origin; // Start vertex of the half-edge.
    HalfEdge *m_twin; // The twin half-edge.
    Face *m_face;     // The face the half-edge bounds.
    HalfEdge *m_next; // Previous edge on the boundary of m_incidentFace.
    IndexType m_id;   // The ID(key) in the half-edge map.
  };

  class Face {
    friend class HalfEdgeMesh;

  public:
    Face() {}

    Face(HalfEdge *outerEdge)
        : m_outerEdge(outerEdge), m_normal(0., 0., 0.), m_id(0) {}

    Face(const Face &other) = delete;

    Face(Face &&other) noexcept {
      m_outerEdge = other.m_outerEdge;
      other.m_outerEdge = nullptr;
      m_normal = std::move(other.m_normal);
      m_id = other.m_id;
    }

    Face &operator=(const Face &other) = delete;

    Face &operator=(Face &&other) noexcept {
      m_outerEdge = other.m_outerEdge;
      other.m_outerEdge = nullptr;
      m_normal = std::move(other.m_normal);
      m_id = other.m_id;
    }

    ~Face() {}

  public:
    class EdgeIterator {
    public:
      EdgeIterator(const Face *face) {
        m_owner = face;
        m_current = face->m_outerEdge;
        m_firstTime = true;
      }

      bool more() const {
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

      void next() { m_current = m_current->next(); }

      const HalfEdge *current() const { return m_current; }

    private:
      const Face *m_owner;
      const HalfEdge *m_current;
      mutable bool m_firstTime;
    };

  public:
    EdgeIterator edgeIter() const { return EdgeIterator(this); }

    Eigen::Vector3<FloatType> normal() const { return m_normal; }

    IndexType id() const { return m_id; }

  private:
    HalfEdge *m_outerEdge; // A half-edge on the outer boundary.
    // std::vector<IndexType> m_innerEdges;
    Eigen::Vector3<FloatType> m_normal; // Face normal.
    IndexType m_id;                     // The ID(key) in the face map.
  };

public:
  HalfEdgeMesh() : m_vertexIndex(0), m_halfEdgeIndex(0), m_faceIndex(0) {}

  /// @brief Construct a half-edge mesh from tr0angle soup.
  HalfEdgeMesh(const TriangleSoup<FloatType, IndexType> &triangleSoup)
      : m_vertexIndex(0), m_halfEdgeIndex(0), m_faceIndex(0) {
    /// Insert vertices.
    for (const Eigen::Vector3<FloatType> &vertex : triangleSoup.vertices()) {
      addVertex({vertex});
    }

    /// Insert faces and their edges.
    /// Twins of the half-edges are not set yet.
    for (const Eigen::Vector3<IndexType> &triangle : triangleSoup.triangles()) {
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

  HalfEdgeMesh(const HalfEdgeMesh &other) = delete;

  HalfEdgeMesh(HalfEdgeMesh &&other) noexcept = default;

  HalfEdgeMesh &operator=(const HalfEdgeMesh &other) = delete;

  HalfEdgeMesh &operator=(HalfEdgeMesh &&other) noexcept = default;

  ~HalfEdgeMesh() {}

public:
  size_t nbVertices() const { return m_vertices.size(); }

  size_t nbFaces() const { return m_faces.size(); }

  const Vertex &vertex(IndexType id) const { return m_vertices.at(id); }

  const HalfEdge &halfEdge(IndexType id) const { return m_halfEdges.at(id); }

  const Face &face(IndexType id) const { return m_faces.at(id); }

  const std::map<IndexType, Vertex> &vertices() const { return m_vertices; }

  const std::map<IndexType, Face> &faces() const { return m_faces; }

private:
  /// @brief
  Vertex &addVertex(Vertex &&vertex) {
    IndexType id = ++m_vertexIndex;
    m_vertices.emplace(id, std::move(vertex));
    Vertex &vert = m_vertices[id];
    vert.m_id = id;
    return vert;
  }

  /// @brief
  HalfEdge &addHalfEdge(HalfEdge &&halfEdge) {
    IndexType id = ++m_halfEdgeIndex;
    m_halfEdges.emplace(id, std::move(halfEdge));
    HalfEdge &edge = m_halfEdges[id];
    edge.m_id = id;
    return edge;
  }

  /// @brief
  Face &addFace(Face &&face) {
    IndexType id = ++m_faceIndex;
    m_faces.emplace(id, std::move(face));
    Face &f = m_faces[id];
    f.m_id = id;
    return f;
  }

  /// @brief Construct edge-twins among `m_halfEdges`.
  /// Use an ordered map to find "duplicate" edges.
  /// Better solution?
  void makeTwins() {
    std::map<std::tuple<IndexType, IndexType>, IndexType> edgeMap{};

    for (auto it = m_halfEdges.cbegin(); it != m_halfEdges.cend(); ++it) {
      IndexType thisV = it->second.m_origin->m_id;
      IndexType nextV = it->second.m_next->m_origin->m_id;

      /// The key is the index of the start and end vertex indices: (a, b),
      /// which a <= b.
      if (thisV > nextV)
        std::swap(thisV, nextV);

      std::tuple<IndexType, IndexType> tup{thisV, nextV};
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

private:
  /// @brief Current vertex index.
  IndexType m_vertexIndex;

  /// @brief Current half-edge index.
  IndexType m_halfEdgeIndex;

  /// @brief Current face index.
  IndexType m_faceIndex;

  /// @brief Vertices.
  std::map<IndexType, Vertex> m_vertices{};

  /// @brief Faces.
  std::map<IndexType, Face> m_faces{};

  /// @brief Half-edges.
  std::map<IndexType, HalfEdge> m_halfEdges{};
};

} // namespace shape
} // namespace naivecgl

#endif
