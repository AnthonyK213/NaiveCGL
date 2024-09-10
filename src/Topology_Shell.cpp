#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Shell);

Shell::Shell() : Naive_Topol() {}

Handle_Naive_Topol Shell::Parent() const { return myParent; }

Handle_Naive_Solid Shell::ParentSolid() const {
  return Handle_Naive_Solid::DownCast(myParent);
}

void Shell::GetBox(Naive_Box &theBox) {}

void Shell::SetParent(const Handle_Naive_Topol &theParent) {
  myParent = theParent.get();
}

Naive_NAMESPACE_END(topology);
