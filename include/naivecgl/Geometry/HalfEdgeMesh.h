#ifndef _NaiveCGL_Shape_HalfEdgeMesh_HeaderFile
#define _NaiveCGL_Shape_HalfEdgeMesh_HeaderFile

#include "TriangleSoup.h"

Naive_Namespace_Begin(geometry);

/// @brief Manifold mesh described by half-edges.
class HalfEdgeMesh {
public:
  class Vertex;
  class HalfEdge;
  class Face;

  class Vertex {
    friend class HalfEdgeMesh;

  public:
    Naive_Export Vertex();

    Naive_Export Vertex(const Naive_Vector3d &theCoord);

    Naive_Export Vertex(Naive_Real theX, Naive_Real theY, Naive_Real theZ);

    Vertex(const Vertex &theOther) = delete;

    Naive_Export Vertex(Vertex &&theOther) noexcept;

    Vertex &operator=(const Vertex &theOther) = delete;

    Naive_Export Vertex &operator=(Vertex &&theOther) noexcept;

    Naive_Export ~Vertex();

  public:
    const Naive_Vector3d &Coord() const { return myCoord; }

    Naive_Vector3d &ChangeCoord() { return myCoord; }

    Naive_Integer Id() const { return myId; }

  private:
    Naive_Vector3d myCoord; // Vertex coordinates.
    HalfEdge *myEdge;      // An half-edge starts with the vertex.
    Naive_Integer myId;     // The ID(key) in the vertex map.
  };

  class HalfEdge {
    friend class HalfEdgeMesh;

  public:
    Naive_Export HalfEdge();

    Naive_Export HalfEdge(Vertex *theOrigin);

    HalfEdge(const HalfEdge &theOther) = delete;

    Naive_Export HalfEdge(HalfEdge &&theOther) noexcept;

    HalfEdge &operator=(const HalfEdge &theOther) = delete;

    Naive_Export HalfEdge &operator=(HalfEdge &&theOther) noexcept;

    Naive_Export ~HalfEdge();

  public:
    const Vertex *Origin() const { return myOrigin; }

    const HalfEdge *Twin() const { return myTwin; }

    const Face *Owner() const { return myFace; }

    const HalfEdge *Next() const { return myNext; }

    Naive_Integer Id() const { return myId; }

  private:
    Vertex *myOrigin;  // Start vertex of the half-edge.
    HalfEdge *myTwin;  // The twin half-edge.
    Face *myFace;      // The face the half-edge bounds.
    HalfEdge *myNext;  // Previous edge on the boundary of myIncidentFace.
    Naive_Integer myId; // The ID(key) in the half-edge map.
  };

  class Face {
    friend class HalfEdgeMesh;

  public:
    Naive_Export Face();

    Naive_Export Face(HalfEdge *theOuterEdge);

    Face(const Face &theOther) = delete;

    Naive_Export Face(Face &&theOther) noexcept;

    Face &operator=(const Face &theOther) = delete;

    Naive_Export Face &operator=(Face &&theOther) noexcept;

    Naive_Export ~Face();

  public:
    class EdgeIterator {
    public:
      EdgeIterator(const Face *theFace);

      Naive_Export Naive_Bool More() const;

      void Next() { myCurrent = myCurrent->Next(); }

      const HalfEdge *Current() const { return myCurrent; }

    private:
      const Face *myOwner;
      const HalfEdge *myCurrent;
      mutable Naive_Bool myFirstTime;
    };

  public:
    EdgeIterator EdgeIter() const { return EdgeIterator(this); }

    Naive_Vector3d Normal() const { return myNormal; }

    Naive_Integer Id() const { return myId; }

  private:
    HalfEdge *myOuterEdge;  // A half-edge on the outer boundary.
    Naive_Vector3d myNormal; // Face normal.
    Naive_Integer myId;      // The ID(key) in the face map.
  };

public:
  Naive_Export HalfEdgeMesh();

  /// @brief Construct a half-edge mesh from a trangle soup.
  Naive_Export HalfEdgeMesh(const TriangleSoup &theTriangleSoup);

  HalfEdgeMesh(const HalfEdgeMesh &theOther) = delete;

  Naive_Export HalfEdgeMesh(HalfEdgeMesh &&theOther) noexcept = default;

  HalfEdgeMesh &operator=(const HalfEdgeMesh &theOther) = delete;

  Naive_Export HalfEdgeMesh &
  operator=(HalfEdgeMesh &&theOther) noexcept = default;

  Naive_Export ~HalfEdgeMesh();

public:
  size_t NbVertices() const { return myVertices.size(); }

  size_t NbFaces() const { return myFaces.size(); }

  const Vertex &GetVertex(Naive_Integer theId) const {
    return myVertices.at(theId);
  }

  const HalfEdge &GetHalfEdge(Naive_Integer theId) const {
    return myHalfEdges.at(theId);
  }

  const Face &GetFace(Naive_Integer theId) const {
    return myFaces.at(theId);
  }

  const Naive_Map<Naive_Integer, Vertex> &Vertices() const {
    return myVertices;
  }

  const Naive_Map<Naive_Integer, Face> &Faces() const {
    return myFaces;
  }

private:
  Vertex &addVertex(Vertex &&theVertex);

  HalfEdge &addHalfEdge(HalfEdge &&theHalfEdge);

  Face &addFace(Face &&theFace);

  /// @brief Construct edge-twins among `myHalfEdges`.
  void makeTwins();

private:
  Naive_Integer myVertexIndex;                       // Current vertex index.
  Naive_Integer myHalfEdgeIndex;                     // Current half-edge index.
  Naive_Integer myFaceIndex;                         // Current face index.
  Naive_Map<Naive_Integer, Vertex> myVertices{};    // Vertices.
  Naive_Map<Naive_Integer, Face> myFaces{};         // Faces.
  Naive_Map<Naive_Integer, HalfEdge> myHalfEdges{}; // Half-edges.
};

Naive_Namespace_End(geometry);

#endif
