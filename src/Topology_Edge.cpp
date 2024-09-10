#include <naivecgl/Geometry/Curve.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Edge);

Edge::Edge()
    : myFin(nullptr), myCrv(nullptr), myBox(),
      myTol(math::Precision::Epsilon0()) {}

Handle_Naive_Topol Edge::Parent() const { return myParent; }

Naive_LinkedList<Handle_Naive_Fin> Edge::GetFins() const {
  if (!myFin)
    return {};

  Naive_LinkedList<Handle_Naive_Fin> aResult{myFin};

  Handle_Naive_Fin aTwin = myFin->Twin();
  while (aTwin != myFin) {
    aResult.push_back(aTwin);
    aTwin = aTwin->Twin();
  }

  return aResult;
}

void Edge::GetBox(Naive_Box &theBox) {}

void Edge::SetParent(const Handle_Naive_Topol &theParent) {
  myParent = theParent.get();
}

Naive_NAMESPACE_END(topology);
