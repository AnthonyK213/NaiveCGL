#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Shell);

Shell::Shell() : Naive_Topol() {}

Handle_Naive_Solid Shell::ParentShell() const {
  return Handle_Naive_Solid::DownCast(myParent);
}

void Shell::GetBox(Naive_Box &theBox) {}

Naive_NAMESPACE_END(topology);
