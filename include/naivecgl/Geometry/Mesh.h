#ifndef _NaiveCGL_Geometry_Mesh_HeaderFile
#define _NaiveCGL_Geometry_Mesh_HeaderFile

#include "../Collection/Map.h"
#include "../Collection/Stack.h"
#include "../Common/Handle.h"
#include "../Math/Pnt3d.h"
#include "../Math/Vec3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Triangulation;

/// @brief Manifold mesh described by half-edges.
class Mesh : public Naive_Object {
public:
  typedef Naive_Integer VertexId;
  typedef Naive_Integer FaceId;

  class HalfEdgeId {
  public:
    Naive_EXPORT HalfEdgeId();

    Naive_EXPORT HalfEdgeId(const VertexId theA, const VertexId theB);

    Naive_EXPORT static const HalfEdgeId &Unset();

    Naive_EXPORT VertexId A() const { return myA; }

    Naive_EXPORT VertexId B() const { return myB; }

    Naive_EXPORT Naive_Bool IsValid() const;

    Naive_EXPORT HalfEdgeId Twin() const { return {myB, myA}; }

    Naive_EXPORT Naive_Bool operator!=(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator==(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator<(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator>(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator<=(const HalfEdgeId &theOther) const;

    Naive_EXPORT Naive_Bool operator>=(const HalfEdgeId &theOther) const;

  private:
    VertexId myA;
    VertexId myB;
  };

  struct Vertex {
    friend class Mesh;

    Naive_EXPORT Vertex();

    Naive_EXPORT Vertex(const Naive_Pnt3d &theCoord);

    Naive_EXPORT Vertex(Naive_Real theX, Naive_Real theY, Naive_Real theZ);

    Naive_EXPORT const Naive_Pnt3d &Coord() const { return myCoord; }

    Naive_EXPORT Naive_Pnt3d &ChangeCoord() { return myCoord; }

    Naive_EXPORT HalfEdgeId Edge() const { return myEdge; }

    Naive_EXPORT VertexId Id() const { return myId; }

  private:
    Naive_Pnt3d myCoord; // Vertex coordinates.
    HalfEdgeId myEdge;   // An half-edge starts with the vertex.
    VertexId myId;       // The ID(key) in the vertex map.
  };

  struct HalfEdge {
    friend class Mesh;

    Naive_EXPORT HalfEdge();

    Naive_EXPORT HalfEdge(const VertexId theOrigin, const VertexId theNext);

    Naive_EXPORT VertexId Origin() const { return myOrigin; }

    Naive_EXPORT FaceId Owner() const { return myFace; }

    Naive_EXPORT HalfEdgeId Twin() const { return myTwin; }

    Naive_EXPORT HalfEdgeId Next() const { return myNext; }

    Naive_EXPORT HalfEdgeId Prev() const { return myPrev; }

    Naive_EXPORT HalfEdgeId Id() const { return myId; }

  private:
    VertexId myOrigin; // Start vertex of the half-edge.
    FaceId myFace;     // The face the half-edge bounds.
    HalfEdgeId myTwin; // The twin half-edge.
    HalfEdgeId myPrev; // Previous edge on the boundary of the incident face.
    HalfEdgeId myNext; // Next edge on the boundary of the incident face.
    HalfEdgeId myId;   // The ID(key) in the half-edge map.
  };

  struct Face {
    friend class Mesh;

    Naive_EXPORT Face();

    Naive_EXPORT Face(const HalfEdgeId theOuterEdge);

    Naive_EXPORT HalfEdgeId Edge() const { return myOuterEdge; }

    Naive_EXPORT Naive_Vec3d Normal() const { return myNormal; }

    Naive_EXPORT FaceId Id() const { return myId; }

  private:
    HalfEdgeId myOuterEdge; // A half-edge on the outer boundary.
    Naive_Vec3d myNormal;   // Face normal.
    FaceId myId;            // The ID(key) in the face map.
  };

  class EdgeIterator {
  public:
    Naive_EXPORT EdgeIterator(const Mesh &theMesh, const FaceId theFace);

    Naive_EXPORT Naive_Bool More() const;

    Naive_EXPORT void Next();

    Naive_EXPORT HalfEdgeId Current() const { return myCurrent; }

  private:
    const Mesh *myMesh;
    const Face *myOwner;
    HalfEdgeId myCurrent;
    mutable Naive_Bool myFirstTime;
  };

public:
  Naive_EXPORT Mesh();

  /// @brief Construct a half-edge mesh from a trangulation.
  Naive_EXPORT explicit Mesh(const Naive_Handle<Triangulation> &thePoly);

  Naive_EXPORT Naive_Bool IsValid() const { return myIsValid; }

  Naive_EXPORT Naive_Size NbVertices() const { return myVertices.size(); }

  Naive_EXPORT Naive_Size NbFaces() const { return myFaces.size(); }

  Naive_EXPORT const Vertex *GetVertex(const VertexId theId) const;

  Naive_EXPORT const HalfEdge *GetHalfEdge(const HalfEdgeId theId) const;

  Naive_EXPORT const Face *GetFace(const FaceId theId) const;

  Naive_EXPORT EdgeIterator EdgeIter(const FaceId theFace) const {
    return {*this, theFace};
  }

  Naive_EXPORT Naive_IntegerList1 GetAllVertices() const;

  Naive_EXPORT Naive_IntegerList1 GetAllFaces() const;

  Naive_EXPORT Naive_Handle<Triangulation>
  GetTriangulation(Naive_Bool theCompat = Naive_False) const;

  Naive_EXPORT Naive_Integer AddVertex(const Naive_Pnt3d &thePoint);

  Naive_EXPORT Naive_Bool RemoveVertex(const VertexId theId);

  Naive_EXPORT FaceId AddFace(const VertexId theV1, const VertexId theV2,
                              const VertexId theV3);

  Naive_EXPORT Naive_Bool RemoveFace(const FaceId theId,
                                     Naive_Bool theCompat = Naive_False);

private:
  Naive_Bool addVertex(const VertexId theId, const Naive_Pnt3d &thePoint);

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

using Naive_Mesh = ::naivecgl::geometry::Mesh;
Naive_DEFINE_HANDLE(Naive_Mesh);

#endif
