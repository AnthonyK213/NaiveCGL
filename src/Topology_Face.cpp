#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Shell.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Face);

Face::Face() : Naive_Topol(), myTol(math::Precision::Epsilon0()) {}

Handle_Naive_Shell Face::ParentShell() const {
  return Handle_Naive_Shell::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
