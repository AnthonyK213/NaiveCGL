#ifndef _NaiveCGL_Shape_HalfEdgeMesh_Header
#define _NaiveCGL_Shape_HalfEdgeMesh_Header

#include "TriangleSoup.h"

Naive_Namespace_Begin(geometry);

/// @brief Manifold mesh described by half-edges.
class Naive_Export HalfEdgeMesh {
public:
  class Vertex;
  class HalfEdge;
  class Face;

  class Naive_Export Vertex {
    friend class HalfEdgeMesh;

  public:
    Vertex();

    Vertex(const Naive_Vector3d &coord);

    Vertex(Naive_Real x, Naive_Real y, Naive_Real z);

    Vertex(const Vertex &other) = delete;

    Vertex(Vertex &&other) noexcept;

    Vertex &operator=(const Vertex &other) = delete;

    Vertex &operator=(Vertex &&other) noexcept;

    ~Vertex();

  public:
    const Naive_Vector3d &coordinates() const { return m_coord; }

    Naive_Vector3d &coordinatesMut() { return m_coord; }

    Naive_Integer id() const { return m_id; }

  private:
    Naive_Vector3d m_coord; // Vertex coordinates.
    HalfEdge *m_edge;       // An half-edge starts with the vertex.
    Naive_Integer m_id;     // The ID(key) in the vertex map.
  };

  class Naive_Export HalfEdge {
    friend class HalfEdgeMesh;

  public:
    HalfEdge();

    HalfEdge(Vertex *origin);

    HalfEdge(const HalfEdge &other) = delete;

    HalfEdge(HalfEdge &&other) noexcept;

    HalfEdge &operator=(const HalfEdge &other) = delete;

    HalfEdge &operator=(HalfEdge &&other) noexcept;

    ~HalfEdge();

  public:
    const Vertex *origin() const { return m_origin; }

    const HalfEdge *twin() const { return m_twin; }

    const Face *face() const { return m_face; }

    const HalfEdge *next() const { return m_next; }

    Naive_Integer id() const { return m_id; }

  private:
    Vertex *m_origin;   // Start vertex of the half-edge.
    HalfEdge *m_twin;   // The twin half-edge.
    Face *m_face;       // The face the half-edge bounds.
    HalfEdge *m_next;   // Previous edge on the boundary of m_incidentFace.
    Naive_Integer m_id; // The ID(key) in the half-edge map.
  };

  class Naive_Export Face {
    friend class HalfEdgeMesh;

  public:
    Face();

    Face(HalfEdge *outerEdge);

    Face(const Face &other) = delete;

    Face(Face &&other) noexcept;

    Face &operator=(const Face &other) = delete;

    Face &operator=(Face &&other) noexcept;

    ~Face();

  public:
    class Naive_Export EdgeIterator {
    public:
      EdgeIterator(const Face *face);

      Naive_Bool more() const;

      void next() { m_current = m_current->next(); }

      const HalfEdge *current() const { return m_current; }

    private:
      const Face *m_owner;
      const HalfEdge *m_current;
      mutable Naive_Bool m_firstTime;
    };

  public:
    EdgeIterator edgeIter() const { return EdgeIterator(this); }

    Naive_Vector3d normal() const { return m_normal; }

    Naive_Integer id() const { return m_id; }

  private:
    HalfEdge *m_outerEdge;   // A half-edge on the outer boundary.
    Naive_Vector3d m_normal; // Face normal.
    Naive_Integer m_id;      // The ID(key) in the face map.
  };

public:
  HalfEdgeMesh();

  /// @brief Construct a half-edge mesh from a trangle soup.
  HalfEdgeMesh(const TriangleSoup &triangleSoup);

  HalfEdgeMesh(const HalfEdgeMesh &other) = delete;

  HalfEdgeMesh(HalfEdgeMesh &&other) noexcept = default;

  HalfEdgeMesh &operator=(const HalfEdgeMesh &other) = delete;

  HalfEdgeMesh &operator=(HalfEdgeMesh &&other) noexcept = default;

  ~HalfEdgeMesh();

public:
  size_t nbVertices() const { return m_vertices.size(); }

  size_t nbFaces() const { return m_faces.size(); }

  const Vertex &vertex(Naive_Integer id) const { return m_vertices.at(id); }

  const HalfEdge &halfEdge(Naive_Integer id) const {
    return m_halfEdges.at(id);
  }

  const Face &face(Naive_Integer id) const { return m_faces.at(id); }

  const Naive_Map<Naive_Integer, Vertex> &vertices() const {
    return m_vertices;
  }

  const Naive_Map<Naive_Integer, Face> &faces() const { return m_faces; }

private:
  Vertex &addVertex(Vertex &&vertex);

  HalfEdge &addHalfEdge(HalfEdge &&halfEdge);

  Face &addFace(Face &&face);

  /// @brief Construct edge-twins among `m_halfEdges`.
  void makeTwins();

private:
  Naive_Integer m_vertexIndex;                      // Current vertex index.
  Naive_Integer m_halfEdgeIndex;                    // Current half-edge index.
  Naive_Integer m_faceIndex;                        // Current face index.
  Naive_Map<Naive_Integer, Vertex> m_vertices{};    // Vertices.
  Naive_Map<Naive_Integer, Face> m_faces{};         // Faces.
  Naive_Map<Naive_Integer, HalfEdge> m_halfEdges{}; // Half-edges.
};

Naive_Namespace_End(geometry);

#endif
