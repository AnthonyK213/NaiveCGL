#ifndef _NaiveCGL_Shape_HalfEdgeMesh_HeaderFile
#define _NaiveCGL_Shape_HalfEdgeMesh_HeaderFile

#include "TriangleSoup.h"

Naive_Namespace_Begin(geometry);

/// @brief Manifold mesh described by half-edges.
class Naive_Export HalfEdgeMesh {
public:
  class Vertex_;
  class HalfEdge_;
  class Face_;

  class Naive_Export Vertex_ {
    friend class HalfEdgeMesh;

  public:
    Vertex_();

    Vertex_(const Naive_Vector3d &theCoord);

    Vertex_(Naive_Real theX, Naive_Real theY, Naive_Real theZ);

    Vertex_(const Vertex_ &theOther) = delete;

    Vertex_(Vertex_ &&theOther) noexcept;

    Vertex_ &operator=(const Vertex_ &theOther) = delete;

    Vertex_ &operator=(Vertex_ &&theOther) noexcept;

    ~Vertex_();

  public:
    const Naive_Vector3d &Coord() const { return myCoord; }

    Naive_Vector3d &ChangeCoord() { return myCoord; }

    Naive_Integer Id() const { return myId; }

  private:
    Naive_Vector3d myCoord; // Vertex coordinates.
    HalfEdge_ *myEdge;      // An half-edge starts with the vertex.
    Naive_Integer myId;     // The ID(key) in the vertex map.
  };

  class Naive_Export HalfEdge_ {
    friend class HalfEdgeMesh;

  public:
    HalfEdge_();

    HalfEdge_(Vertex_ *theOrigin);

    HalfEdge_(const HalfEdge_ &theOther) = delete;

    HalfEdge_(HalfEdge_ &&theOther) noexcept;

    HalfEdge_ &operator=(const HalfEdge_ &theOther) = delete;

    HalfEdge_ &operator=(HalfEdge_ &&theOther) noexcept;

    ~HalfEdge_();

  public:
    const Vertex_ *Origin() const { return myOrigin; }

    const HalfEdge_ *Twin() const { return myTwin; }

    const Face_ *Face() const { return myFace; }

    const HalfEdge_ *Next() const { return myNext; }

    Naive_Integer Id() const { return myId; }

  private:
    Vertex_ *myOrigin;  // Start vertex of the half-edge.
    HalfEdge_ *myTwin;  // The twin half-edge.
    Face_ *myFace;      // The face the half-edge bounds.
    HalfEdge_ *myNext;  // Previous edge on the boundary of myIncidentFace.
    Naive_Integer myId; // The ID(key) in the half-edge map.
  };

  class Naive_Export Face_ {
    friend class HalfEdgeMesh;

  public:
    Face_();

    Face_(HalfEdge_ *theOuterEdge);

    Face_(const Face_ &theOther) = delete;

    Face_(Face_ &&theOther) noexcept;

    Face_ &operator=(const Face_ &theOther) = delete;

    Face_ &operator=(Face_ &&theOther) noexcept;

    ~Face_();

  public:
    class Naive_Export EdgeIterator {
    public:
      EdgeIterator(const Face_ *theFace);

      Naive_Bool More() const;

      void Next() { myCurrent = myCurrent->Next(); }

      const HalfEdge_ *Current() const { return myCurrent; }

    private:
      const Face_ *myOwner;
      const HalfEdge_ *myCurrent;
      mutable Naive_Bool myFirstTime;
    };

  public:
    EdgeIterator EdgeIter() const { return EdgeIterator(this); }

    Naive_Vector3d Normal() const { return myNormal; }

    Naive_Integer Id() const { return myId; }

  private:
    HalfEdge_ *myOuterEdge;  // A half-edge on the outer boundary.
    Naive_Vector3d myNormal; // Face normal.
    Naive_Integer myId;      // The ID(key) in the face map.
  };

public:
  HalfEdgeMesh();

  /// @brief Construct a half-edge mesh from a trangle soup.
  HalfEdgeMesh(const TriangleSoup &theTriangleSoup);

  HalfEdgeMesh(const HalfEdgeMesh &theOther) = delete;

  HalfEdgeMesh(HalfEdgeMesh &&theOther) noexcept = default;

  HalfEdgeMesh &operator=(const HalfEdgeMesh &theOther) = delete;

  HalfEdgeMesh &operator=(HalfEdgeMesh &&theOther) noexcept = default;

  ~HalfEdgeMesh();

public:
  size_t NbVertices() const { return myVertices.size(); }

  size_t NbFaces() const { return myFaces.size(); }

  const Vertex_ &Vertex(Naive_Integer theId) const {
    return myVertices.at(theId);
  }

  const HalfEdge_ &HalfEdge(Naive_Integer theId) const {
    return myHalfEdges.at(theId);
  }

  const Face_ &Face(Naive_Integer theId) const { return myFaces.at(theId); }

  const Naive_Map<Naive_Integer, Vertex_> &Vertices() const {
    return myVertices;
  }

  const Naive_Map<Naive_Integer, Face_> &Faces() const { return myFaces; }

private:
  Vertex_ &addVertex(Vertex_ &&theVertex);

  HalfEdge_ &addHalfEdge(HalfEdge_ &&theHalfEdge);

  Face_ &addFace(Face_ &&theFace);

  /// @brief Construct edge-twins among `myHalfEdges`.
  void makeTwins();

private:
  Naive_Integer myVertexIndex;                       // Current vertex index.
  Naive_Integer myHalfEdgeIndex;                     // Current half-edge index.
  Naive_Integer myFaceIndex;                         // Current face index.
  Naive_Map<Naive_Integer, Vertex_> myVertices{};    // Vertices.
  Naive_Map<Naive_Integer, Face_> myFaces{};         // Faces.
  Naive_Map<Naive_Integer, HalfEdge_> myHalfEdges{}; // Half-edges.
};

Naive_Namespace_End(geometry);

#endif
