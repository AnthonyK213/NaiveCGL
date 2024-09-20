#include <naivecgl/Geometry/Curve.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Edge);

Edge::Edge()
    : myParent(nullptr), myPrev(nullptr), myNext(nullptr), myFin(nullptr),
      myCrv(nullptr), myBox(), myTol(math::Precision::Epsilon0()) {
  init();
  setVertex(nullptr, Naive_True);
  setVertex(nullptr, Naive_False);
}

Edge::Edge(const Handle_Naive_Vertex &theBackward,
           const Handle_Naive_Vertex &theForward)
    : myParent(nullptr), myPrev(nullptr), myNext(nullptr), myFin(nullptr),
      myCrv(nullptr), myBox(), myTol(math::Precision::Epsilon0()) {
  init();
  setVertex(theForward, Naive_True);
  setVertex(theBackward, Naive_False);
}

Edge::~Edge() { myFin.Nullify(); }

Naive_Topol *Edge::Parent() const { return myParent; }

const Handle_Naive_Vertex &Edge::GetVertex(Naive_Bool theForward) {
  return theForward ? (ForwardFin()->GetVertex())
                    : (BackwardFin()->GetVertex());
}

const Handle_Naive_Fin &Edge::ForwardFin() const { return myFin; }

const Handle_Naive_Fin &Edge::BackwardFin() const { return myFin->Twin(); }

Naive_LinkedList<Handle_Naive_Fin>
Edge::GetFins(const Naive_Bool theIncludeDummy) const {
  Naive_LinkedList<Handle_Naive_Fin> aResult{};

  if (theIncludeDummy) {
    aResult.push_back(myFin);

    Handle_Naive_Fin aTwin = myFin->Twin();
    while (aTwin != myFin) {
      aResult.push_back(aTwin);
      aTwin = aTwin->Twin();
    }
  } else {
    if (!myFin->IsDummy())
      aResult.push_back(myFin);

    Handle_Naive_Fin aTwin = myFin->Twin();
    while (aTwin != myFin) {
      if (!aTwin->IsDummy())
        aResult.push_back(aTwin);
      aTwin = aTwin->Twin();
    }
  }

  return aResult;
}

const Handle_Naive_Curve &Edge::GetCurve() const { return myCrv; }

void Edge::GetBox(Naive_Box &theBox) { Naive_TODO; }

Naive_Bool Edge::IsManifold() const {
  return BackwardFin()->Twin() == ForwardFin();
}

void Edge::SetParent(Naive_Topol *theParent) { myParent = theParent; }

void Edge::init() {
  myFin = new Naive_Fin(this, nullptr, Naive_True);
  Handle_Naive_Fin aTwin = new Naive_Fin(this, nullptr, Naive_False);
  myFin->myTwin = aTwin;
  aTwin->myTwin = myFin;
}

void Edge::setVertex(const Handle_Naive_Vertex &theVert,
                     Naive_Bool theForward) {
  Naive_Fin *aFin = (theForward ? ForwardFin() : BackwardFin()).get();

  if (aFin->myVert == theVert)
    return;

  /* Remove aFin from aFin->myVert->myFin */
  if (aFin->myVert) {
    Naive_Fin *aPrev = nullptr;
    Naive_Fin *aCurr = aFin->myVert->myFin;
    while (aCurr) {
      if (aFin == aCurr) {
        if (!aPrev)
          aFin->myVert->myFin = aCurr->Comp();
        else
          aPrev->myComp = aCurr->Comp();
        break;
      }
      aPrev = aCurr;
      aCurr = aCurr->Comp();
    }
  }

  aFin->myVert = theVert;

  /* Add aFin to theVert->myFin */
  if (theVert) {
    aFin->myComp = theVert->myFin;
    theVert->myFin = aFin;
  }
}

Naive_NAMESPACE_END(topology);
