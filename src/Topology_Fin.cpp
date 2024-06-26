#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>

Naive_NAMESPACE_BEGIN(topology);

Fin::Fin() : Naive_Topol() {}

Naive_Class Fin::Class() const { return Naive_Class_fin; }

Handle_Naive_Loop Fin::ParentLoop() const {
  return Handle_Naive_Loop::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
