#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Shell);

Shell::Shell() : Naive_Topol() {}

Handle_Naive_Solid Shell::ParentShell() const {
  return Handle_Naive_Solid::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
