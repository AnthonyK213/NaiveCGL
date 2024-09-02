#ifndef _NaiveCGL_Topology_Edge_HeaderFile
#define _NaiveCGL_Topology_Edge_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Curve;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Fin;
class Vertex;

class Edge final : public Naive_Topol {
  friend class eulerop::SplitEdge;

public:
  Naive_EXPORT Edge();

  Naive_EXPORT Naive_Handle<Fin> ParentFin() const;

  Naive_DEFINE_RTTI(Edge, Naive_Topol);

private:
  Naive_Real myTol;
  Naive_Handle<geometry::Curve> myCrv;
  Naive_Handle<Vertex> myVerts[2];
};

Naive_NAMESPACE_END(topology);

using Naive_Edge = ::naivecgl::topology::Edge;
Naive_DEFINE_HANDLE(Naive_Edge);

#endif
