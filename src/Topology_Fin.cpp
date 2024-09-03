#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Fin);

Fin::Fin() : Naive_Topol() {}

Handle_Naive_Loop Fin::ParentLoop() const {
  return Handle_Naive_Loop::DownCast(myParent);
}

Handle_Naive_Edge Fin::ParentEdge() const { return myEdge; }

Naive_NAMESPACE_END(topology);
