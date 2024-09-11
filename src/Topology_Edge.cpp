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
  return theForward ? (myFin->GetVertex()) : (myFin->myTwin->GetVertex());
}

const Handle_Naive_Fin &Edge::GetHeadFin() const { return myFin; }

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

const Handle_Naive_Curve &Edge::GetCurve() const { return myCrv; }

void Edge::GetBox(Naive_Box &theBox) {}

void Edge::SetParent(Naive_Topol *theParent) { myParent = theParent; }

void Edge::init() {
  myFin = new Naive_Fin(this, nullptr, Naive_True);
  Handle_Naive_Fin aTwin = new Naive_Fin(this, nullptr, Naive_False);
  myFin->myTwin = aTwin;
  aTwin->myTwin = myFin;
}

void Edge::setVertex(const Handle_Naive_Vertex &theVert,
                     Naive_Bool theForward) {
  if (theForward) {
    myFin->myVert = theVert;
    theVert->myFin = myFin.get();
  } else {
    myFin->Twin()->myVert = theVert;
    theVert->myFin = myFin->Twin().get();
  }
}

Naive_NAMESPACE_END(topology);
