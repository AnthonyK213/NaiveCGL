#ifndef _NaiveCGL_Topology_Edge_HeaderFile
#define _NaiveCGL_Topology_Edge_HeaderFile

#include "../Geometry/Curve.h"
#include "Vertex.h"

Naive_NAMESPACE_BEGIN(topology);

class Fin;

class Edge final : public Naive_Topol {
public:
  Naive_EXPORT Edge();

  Naive_EXPORT Naive_Handle<Fin> ParentFin() const;

  Naive_DEFINE_RTTI(Edge, Naive_Topol, Naive_Class_edge);

private:
  Naive_Real myTol;
  Handle_Naive_Curve myCrv;
  Handle_Naive_Vertex myVerts[2];
};

Naive_NAMESPACE_END(topology);

using Naive_Edge = ::naivecgl::topology::Edge;
Naive_DEFINE_HANDLE(Naive_Edge);

#endif
