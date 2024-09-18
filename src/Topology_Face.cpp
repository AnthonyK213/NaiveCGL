#include <naivecgl/Geometry/Surface.h>
#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Shell.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Face);

Face::Face()
    : myLoops(), myShell(nullptr), myPrev(nullptr), myNext(nullptr),
      mySrf(nullptr), myBox(), myTol(math::Precision::Epsilon0()) {
  Handle_Naive_Loop aLoop = new Naive_Loop;
  aLoop->myFace = this;
  myLoops.push_back(aLoop);
}

Naive_Topol *Face::Parent() const { return myShell; }

Naive_Shell *Face::ParentShell() const { return myShell; }

Handle_Naive_Loop Face::OuterLoop() const { return myLoops.front(); }

void Face::GetBox(Naive_Box &theBox) {}

void Face::SetParent(Naive_Topol *theParent) {
  myShell = dynamic_cast<Naive_Shell *>(theParent);
}

Naive_NAMESPACE_END(topology);
