#ifndef NAIVECGL_SHAPE_HALF_EDGE_MESH_H
#define NAIVECGL_SHAPE_HALF_EDGE_MESH_H

#include <Eigen/Eigen>
#include <map>
#include <tuple>
#include <vector>

namespace naivecgl {
namespace shape {

#if 0
// typedef double FloatType;
// typedef size_t IndexType;
// class __declspec(dllexport) HalfEdgeMesh {
#else
template <typename FloatType, typename IndexType> class HalfEdgeMesh {
#endif

public:
  struct Vertex {
    Eigen::Vector3<FloatType> m_coord; // Vertex coordinates.
    IndexType m_edge;                  // An half-edge starts with the vertex.
  };

  struct HalfEdge {
    IndexType m_origin; // Start vertex of the half-edge.
    IndexType m_twin;   // The twin half-edge.
    IndexType m_face;   // The face the half-edge bounds.
    IndexType m_next;   // Previous edge on the boundary of m_incidentFace.
    IndexType m_prev;   // Next edge on the boundary of m_incidentFace.
  };

  struct Face {
    IndexType m_outerEdge; // A half-edge on the outer boundary.
    // std::vector<IndexType> m_innerEdges;
    Eigen::Vector3<FloatType> m_normal; // Face normal.
  };

public:
  HalfEdgeMesh() : m_vertexIndex(0), m_halfEdgeIndex(0), m_faceIndex(0) {}

  /// @brief Construct a half-edge mesh from triangle soup.
  /// @param vertices Vertices.
  /// @param triangles Triangles.
  HalfEdgeMesh(const std::vector<Eigen::Vector3<FloatType>> &vertices,
               const std::vector<Eigen::Vector3<IndexType>> &triangles)
      : m_vertexIndex(0), m_halfEdgeIndex(0), m_faceIndex(0) {
    /// Insert vertices.
    for (const Eigen::Vector3<FloatType> &vertex : vertices) {
      addVertex({vertex, 0});
    }

    /// Insert faces and their edges.
    /// Twins of the half-edges are not set yet.
    for (const Eigen::Vector3<IndexType> &triangle : triangles) {
      IndexType index0 = addHalfEdge({triangle(0), 0, 0, 0, 0});
      IndexType index1 = addHalfEdge({triangle(1), 0, 0, 0, 0});
      IndexType index2 = addHalfEdge({triangle(2), 0, 0, 0, 0});

      m_halfEdges[index0].m_next = index1;
      m_halfEdges[index1].m_next = index2;
      m_halfEdges[index2].m_next = index0;

      m_halfEdges[index0].m_prev = index2;
      m_halfEdges[index1].m_prev = index0;
      m_halfEdges[index2].m_prev = index1;

      IndexType faceIndex = addFace({index0, {0., 0., 0.}});

      m_halfEdges[index0].m_face = faceIndex;
      m_halfEdges[index1].m_face = faceIndex;
      m_halfEdges[index2].m_face = faceIndex;
    }

    /// Make edge twins.
    std::map<std::tuple<IndexType, IndexType>, IndexType> edgeMap{};

    for (auto it = m_halfEdges.cbegin(); it != m_halfEdges.cend(); ++it) {
      IndexType thisV = it->second.m_origin;
      IndexType nextV = m_halfEdges[it->second.m_next].m_origin;
      std::tuple<IndexType, IndexType> tup{std::min(thisV, nextV),
                                           std::max(thisV, nextV)};

      auto key = edgeMap.find(tup);

      if (key == edgeMap.cend()) {
        edgeMap.insert(std::make_pair(tup, it->first));
        continue;
      }

      IndexType twinIndex = edgeMap[key->first];

      m_halfEdges[twinIndex].m_twin = it->first;
      m_halfEdges[it->first].m_twin = twinIndex;
    }
  }

  ~HalfEdgeMesh() {}

private:
  /// @brief
  IndexType addVertex(const Vertex &vertex) {
    m_vertices.insert(std::make_pair(++m_vertexIndex, vertex));
    return m_vertexIndex;
  }

  /// @brief
  IndexType addHalfEdge(const HalfEdge &halfEdge) {
    m_halfEdges.insert(std::make_pair(++m_halfEdgeIndex, halfEdge));
    return m_halfEdgeIndex;
  }

  /// @brief
  IndexType addFace(const Face &face) {
    m_faces.insert(std::make_pair(++m_faceIndex, face));
    return m_faceIndex;
  }

private:
  /// @brief Current vertex index.
  IndexType m_vertexIndex;

  /// @brief Current half-edge index.
  IndexType m_halfEdgeIndex;

  /// @brief Current face index.
  IndexType m_faceIndex;

  std::map<IndexType, Vertex> m_vertices{};

  std::map<IndexType, Face> m_faces{};

  std::map<IndexType, HalfEdge> m_halfEdges{};
};

} // namespace shape
} // namespace naivecgl

#endif
