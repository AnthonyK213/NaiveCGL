#ifndef _NaiveCGL_Topology_Vertex_HeaderFile
#define _NaiveCGL_Topology_Vertex_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Point3d;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Edge;
class Fin;

class Vertex final : public Naive_Topol {
  friend class Edge;
  friend class Fin;
  friend class eulerop::MakeBodyFaceVertex;
  friend class eulerop::SplitEdge;

public:
  Naive_EXPORT Vertex();

  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Code
  AttachPoint(const Naive_Handle<geometry::Point3d> &aPoint);

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsManifold() const;

  Naive_DEFINE_RTTI(Vertex, Naive_Topol);

protected:
  Naive_EXPORT virtual void SetParent(Naive_Topol *theParent) Naive_OVERRIDE;

private:
  Naive_Topol *myParent; /* Parent shell or body. */
  Fin *myFin;     /* Head of single-linked list of fins ponit to the vertex. */
  Vertex *myPrev; /* Previous vertex in myParent. */
  Naive_Handle<Vertex> myNext; /* Next vertex in myParent. */
  Naive_Handle<geometry::Point3d> myPnt;
  Naive_Real myTol;
};

Naive_NAMESPACE_END(topology);

using Naive_Vertex = ::naivecgl::topology::Vertex;
Naive_DEFINE_HANDLE(Naive_Vertex);

#endif
