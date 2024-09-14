#include <naivecgl/Geometry/Curve.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Fin);

Fin::Fin(const Handle_Naive_Edge &theEdge, const Handle_Naive_Vertex &theVert,
         Naive_Bool theSense)
    : myLoop(nullptr), myEdge(theEdge.get()), myCrv(nullptr), myVert(theVert),
      myTwin(nullptr), myPrev(nullptr), myNext(nullptr), myComp(nullptr),
      mySense(theSense) {
  theVert->myFin = this;
}

Naive_Topol *Fin::Parent() const { return myEdge; }

Naive_Loop *Fin::ParentLoop() const { return myLoop; }

Edge *Fin::ParentEdge() const { return myEdge; }

const Handle_Naive_Vertex &Fin::GetVertex() const { return myVert; }

const Handle_Naive_Curve &Fin::GetCurve() const {
  return myCrv ? myCrv : myEdge->GetCurve();
}

const Handle_Naive_Fin &Fin::Twin() const { return myTwin; }

Naive_Fin *Fin::Prev() const { return myPrev; }

Naive_Fin *Fin::Next() const { return myNext; }

Naive_Fin *Fin::Comp() const { return myComp; }

Naive_Bool Fin::Sense() const { return mySense; }

Naive_Bool Fin::IsDummy() const { return myLoop == nullptr; }

Naive_NAMESPACE_END(topology);
