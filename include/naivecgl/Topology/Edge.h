#ifndef _NaiveCGL_Topology_Edge_HeaderFile
#define _NaiveCGL_Topology_Edge_HeaderFile

#include "../Collection/LinkedList.h"
#include "../Math/Box.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Curve;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Body;
class Fin;
class Vertex;

class Edge final : public Naive_Topol {
  friend class eulerop::SplitEdge;

public:
  Naive_EXPORT Edge();

  Naive_EXPORT Naive_Handle<Body> ParentBody() const;

  Naive_EXPORT Naive_LinkedList<Naive_Handle<Fin>> GetFins() const;

  Naive_DEFINE_RTTI(Edge, Naive_Topol);

protected:
  Naive_EXPORT virtual void UpdateBox(math::Box *theBox) Naive_OVERRIDE;

private:
  Naive_Handle<geometry::Curve> myCrv;
  Naive_Handle<Vertex> myVerts[2];
  Naive_Handle<Fin> myFin;
  Naive_Box myBox;
  Naive_Real myTol;
};

Naive_NAMESPACE_END(topology);

using Naive_Edge = ::naivecgl::topology::Edge;
Naive_DEFINE_HANDLE(Naive_Edge);

#endif
