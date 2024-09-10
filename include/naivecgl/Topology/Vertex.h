#ifndef _NaiveCGL_Topology_Vertex_HeaderFile
#define _NaiveCGL_Topology_Vertex_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Point3d;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Edge;

class Vertex final : public Naive_Topol {
public:
  Naive_EXPORT Vertex();

  Naive_EXPORT Naive_Handle<Edge> ParentEdge() const;

  Naive_EXPORT Naive_Code
  AttachPoint(const Naive_Handle<geometry::Point3d> &aPoint);

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Vertex, Naive_Topol);

private:
  Naive_Handle<geometry::Point3d> myPnt;
  Naive_Real myTol;
};

Naive_NAMESPACE_END(topology);

using Naive_Vertex = ::naivecgl::topology::Vertex;
Naive_DEFINE_HANDLE(Naive_Vertex);

#endif
