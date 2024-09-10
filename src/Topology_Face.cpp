#include <naivecgl/Geometry/Surface.h>
#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Shell.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Face);

Face::Face() : Naive_Topol(), myTol(math::Precision::Epsilon0()) {}

Handle_Naive_Topol Face::Parent() const { return myShell; }

Handle_Naive_Shell Face::ParentShell() const { return myShell; }

void Face::GetBox(Naive_Box &theBox) {}

void Face::SetParent(const Handle_Naive_Topol &theParent) {
  auto aShell = Handle_Naive_Shell::DownCast(theParent);
  if (aShell)
    myShell = aShell.get();
}

Naive_NAMESPACE_END(topology);
