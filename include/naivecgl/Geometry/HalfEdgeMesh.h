#ifndef _NaiveCGL_Shape_HalfEdgeMesh_HeaderFile
#define _NaiveCGL_Shape_HalfEdgeMesh_HeaderFile

#include "Point3d.h"
#include "TriangleSoup.h"

#include <naivecgl/Common/Handle.h>

#include <stack>

Naive_NAMESPACE_BEGIN(geometry);

/// @brief Manifold mesh described by half-edges.
class HalfEdgeMesh : public Naive_Transient {
public:
  class Vertex;
  class HalfEdge;
  class Face;

  class Vertex {
    friend class HalfEdgeMesh;

  public:
    Naive_EXPORT Vertex();

    Naive_EXPORT Vertex(const Naive_Point3d &theCoord);

    Naive_EXPORT Vertex(Naive_Real theX, Naive_Real theY, Naive_Real theZ);

    Vertex(const Vertex &theOther) = delete;

    Naive_EXPORT Vertex(Vertex &&theOther) noexcept;

    Vertex &operator=(const Vertex &theOther) = delete;

    Naive_EXPORT Vertex &operator=(Vertex &&theOther) noexcept;

    Naive_EXPORT ~Vertex();

  public:
    const Naive_Point3d &Coord() const { return myCoord; }

    Naive_Point3d &ChangeCoord() { return myCoord; }

    // HalfEdge *Edge() const { return myEdge; }

    Naive_Integer Id() const { return myId; }

  private:
    Naive_Point3d myCoord; // Vertex coordinates.
    HalfEdge *myEdge;      // An half-edge starts with the vertex.
    Naive_Integer myId;    // The ID(key) in the vertex map.
  };

  class HalfEdgeId {
  public:
    Naive_EXPORT HalfEdgeId();

    Naive_EXPORT HalfEdgeId(const Naive_Integer theA, const Naive_Integer theB);

    Naive_EXPORT Naive_Integer A() const { return myA; }

    Naive_EXPORT Naive_Integer B() const { return myB; }

    Naive_EXPORT Naive_Bool IsValid() const;

    Naive_EXPORT HalfEdgeId Twin() const { return {myB, myA}; }

    Naive_EXPORT Naive_Bool operator!=(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator==(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator<(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator>(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator<=(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator>=(const HalfEdgeId &theOther) const;

  private:
    Naive_Integer myA;
    Naive_Integer myB;
  };

  class HalfEdge {
    friend class HalfEdgeMesh;

  public:
    Naive_EXPORT HalfEdge();

    Naive_EXPORT HalfEdge(Vertex *theOrigin, Vertex *theNext);

    HalfEdge(const HalfEdge &theOther) = delete;

    Naive_EXPORT HalfEdge(HalfEdge &&theOther) noexcept;

    HalfEdge &operator=(const HalfEdge &theOther) = delete;

    Naive_EXPORT HalfEdge &operator=(HalfEdge &&theOther) noexcept;

    Naive_EXPORT ~HalfEdge();

  public:
    Naive_EXPORT const Vertex *Origin() const { return myOrigin; }

    Naive_EXPORT const HalfEdge *Twin() const { return myTwin; }

    Naive_EXPORT const Face *Owner() const { return myFace; }

    Naive_EXPORT const HalfEdge *Next() const { return myNext; }

    Naive_EXPORT const HalfEdge *Prev() const { return myPrev; }

    Naive_EXPORT const HalfEdgeId &Id() const { return myId; }

  private:
    Vertex *myOrigin; // Start vertex of the half-edge.
    HalfEdge *myTwin; // The twin half-edge.
    Face *myFace;     // The face the half-edge bounds.
    HalfEdge *myPrev; // Previous edge on the boundary of the incident face.
    HalfEdge *myNext; // Next edge on the boundary of the incident face.
    HalfEdgeId myId;  // The ID(key) in the half-edge map.
  };

  class Face {
    friend class HalfEdgeMesh;

  public:
    Naive_EXPORT Face();

    Naive_EXPORT Face(HalfEdge *theOuterEdge);

    Face(const Face &theOther) = delete;

    Naive_EXPORT Face(Face &&theOther) noexcept;

    Face &operator=(const Face &theOther) = delete;

    Naive_EXPORT Face &operator=(Face &&theOther) noexcept;

    Naive_EXPORT ~Face();

  public:
    class EdgeIterator {
    public:
      Naive_EXPORT EdgeIterator(const Face *theFace);

      Naive_EXPORT Naive_Bool More() const;

      Naive_EXPORT void Next() { myCurrent = myCurrent->Next(); }

      Naive_EXPORT const HalfEdge *Current() const { return myCurrent; }

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
    HalfEdge *myOuterEdge;   // A half-edge on the outer boundary.
    Naive_Vector3d myNormal; // Face normal.
    Naive_Integer myId;      // The ID(key) in the face map.
  };

public:
  Naive_EXPORT HalfEdgeMesh();

  /// @brief Construct a half-edge mesh from a trangle soup.
  Naive_EXPORT explicit HalfEdgeMesh(const TriangleSoup &theTriangleSoup);

  HalfEdgeMesh(const HalfEdgeMesh &theOther) = delete;

  Naive_EXPORT HalfEdgeMesh(HalfEdgeMesh &&theOther) noexcept = default;

  HalfEdgeMesh &operator=(const HalfEdgeMesh &theOther) = delete;

  Naive_EXPORT HalfEdgeMesh &
  operator=(HalfEdgeMesh &&theOther) noexcept = default;

  Naive_EXPORT ~HalfEdgeMesh();

public:
  Naive_EXPORT Naive_Bool IsValid() const { return myIsValid; }

  Naive_EXPORT Naive_Size NbVertices() const { return myVertices.size(); }

  Naive_EXPORT Naive_Size NbFaces() const { return myFaces.size(); }

  Naive_EXPORT const Vertex *GetVertex(Naive_Integer theId) const;

  Naive_EXPORT const HalfEdge *GetHalfEdge(const HalfEdgeId &theId) const;

  Naive_EXPORT const Face *GetFace(Naive_Integer theId) const;

  Naive_EXPORT Naive_IntegerList GetAllVertices() const;

  Naive_EXPORT Naive_IntegerList GetAllFaces() const;

  Naive_EXPORT Handle_Naive_Poly Soup(Naive_Bool theCompat = false) const;

  Naive_EXPORT Naive_Integer AddVertex(const Naive_Point3d &thePoint);

  Naive_EXPORT Naive_Bool RemoveVertex(Naive_Integer theId);

  Naive_EXPORT Naive_Integer AddFace(Naive_Integer theV1, Naive_Integer theV2,
                                     Naive_Integer theV3);

  Naive_EXPORT Naive_Bool RemoveFace(Naive_Integer theId,
                                     Naive_Bool theCompat = false);

private:
  Naive_Bool addVertex(Naive_Integer theId, const Naive_Point3d &thePoint);

  Naive_Bool removeHalfEdge(const HalfEdge *theEdge, Naive_Bool theCompat);

private:
  Naive_Integer myVertexIndex; // Current vertex index.
  Naive_Integer myFaceIndex;   // Current face index.
  Naive_Stack<Naive_Integer> myVertexSlots;
  Naive_Stack<Naive_Integer> myFaceSlots;
  Naive_Map<Naive_Integer, Vertex> myVertices; // Vertices.
  Naive_Map<HalfEdgeId, HalfEdge> myHalfEdges; // Half-edges.
  Naive_Map<Naive_Integer, Face> myFaces;      // Faces.
  Naive_Bool myIsValid;
};

Naive_NAMESPACE_END(geometry);

using Naive_Mesh = ::naivecgl::geometry::HalfEdgeMesh;
using Handle_Naive_Mesh = Naive_Handle<Naive_Mesh>;

#endif
