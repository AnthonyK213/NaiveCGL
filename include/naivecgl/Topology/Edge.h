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

  Naive_EXPORT virtual Naive_Handle<Topol> Parent() const Naive_OVERRIDE;

  Naive_EXPORT Naive_LinkedList<Naive_Handle<Fin>> GetFins() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Edge, Naive_Topol);

protected:
  Naive_EXPORT virtual void
  SetParent(const Handle_Naive_Topol &theParent) Naive_OVERRIDE;

private:
  Naive_Topol *myParent;
  Naive_Handle<Fin> myFin;
  Naive_Handle<geometry::Curve> myCrv;
  Naive_Box myBox;
  Naive_Real myTol;
};

Naive_NAMESPACE_END(topology);

using Naive_Edge = ::naivecgl::topology::Edge;
Naive_DEFINE_HANDLE(Naive_Edge);

#endif
