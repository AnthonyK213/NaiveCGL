#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Shell.h>

Naive_NAMESPACE_BEGIN(topology);

Face::Face() : Naive_Topol(), myTol(math::Precision::Epsilon0()) {}

Naive_Class Face::Class() const { return Naive_Class_face; }

Handle_Naive_Shell Face::ParentShell() const {
  return Handle_Naive_Shell::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
