#ifndef NAIVECGL_SHAPE_HALF_EDGE_MESH_H
#define NAIVECGL_SHAPE_HALF_EDGE_MESH_H

#include <Eigen/Eigen>
#include <map>
#include <tuple>
#include <vector>

#include "TriangleSoup.hpp"

namespace naivecgl {
namespace shape {

/// @brief Manifold mesh described by half-edges.
/// @tparam FloatType
/// @tparam IndexType
template <typename FloatType, typename IndexType> class HalfEdgeMesh {
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
  HalfEdgeMesh(const TriangleSoup<FloatType, IndexType> &triangleSoup)
      : m_vertexIndex(0), m_halfEdgeIndex(0), m_faceIndex(0) {
    /// Insert vertices.
    for (const Eigen::Vector3<FloatType> &vertex : triangleSoup.vertices()) {
      addVertex({vertex, 0});
    }

    /// Insert faces and their edges.
    /// Twins of the half-edges are not set yet.
    for (const Eigen::Vector3<IndexType> &triangle : triangleSoup.triangles()) {
      /// Vertex key starts from 1!
      IndexType index0 = addHalfEdge({triangle(0) + 1, 0, 0, 0, 0});
      IndexType index1 = addHalfEdge({triangle(1) + 1, 0, 0, 0, 0});
      IndexType index2 = addHalfEdge({triangle(2) + 1, 0, 0, 0, 0});

      HalfEdge &edge0 = m_halfEdges[index0];
      HalfEdge &edge1 = m_halfEdges[index1];
      HalfEdge &edge2 = m_halfEdges[index2];

      edge0.m_next = index1;
      edge1.m_next = index2;
      edge2.m_next = index0;

      edge0.m_prev = index2;
      edge1.m_prev = index0;
      edge2.m_prev = index1;

      /// TODO: Boundary check.
      m_vertices[edge0.m_origin].m_edge = index0;
      m_vertices[edge1.m_origin].m_edge = index1;
      m_vertices[edge2.m_origin].m_edge = index2;

      IndexType faceIndex = addFace({index0, {0., 0., 0.}});

      /// Store face index in the boundary edges.
      edge0.m_face = faceIndex;
      edge1.m_face = faceIndex;
      edge2.m_face = faceIndex;
    }

    /// Construct edge-twins.
    /// Use an ordered map to find "duplicate" edges.
    /// Better solution?
    std::map<std::tuple<IndexType, IndexType>, IndexType> edgeMap{};

    for (auto it = m_halfEdges.cbegin(); it != m_halfEdges.cend(); ++it) {
      IndexType thisV = it->second.m_origin;
      IndexType nextV = m_halfEdges[it->second.m_next].m_origin;

      /// The key is the index of the start and end vertex indices: (a, b),
      /// which a <= b.
      if (thisV > nextV)
        std::swap(thisV, nextV);

      std::tuple<IndexType, IndexType> tup{thisV, nextV};
      auto key = edgeMap.find(tup);

      /// If the edge is not in the `edgeMap`, just insert the pair.
      if (key == edgeMap.cend()) {
        edgeMap.insert(std::make_pair(tup, it->first));
        continue;
      }

      /// Find the "duplicate" edges, make them twins.
      IndexType twinIndex = key->second;
      m_halfEdges[twinIndex].m_twin = it->first;
      m_halfEdges[it->first].m_twin = twinIndex;
    }
  }

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
