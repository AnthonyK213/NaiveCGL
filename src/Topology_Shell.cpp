#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Shell::Shell() : Naive_Topol() {}

Naive_Class Shell::Class() const { return Naive_Class_shell; }

Handle_Naive_Solid Shell::ParentShell() const {
  return Handle_Naive_Solid::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
