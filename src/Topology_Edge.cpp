#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>

Naive_NAMESPACE_BEGIN(topology);

Edge::Edge() : Naive_Topol(), myTol(math::Precision::Epsilon0()) {}

Naive_Class Edge::Class() const { return Naive_Class_edge; }

Handle_Naive_Fin Edge::ParentFin() const {
  return Handle_Naive_Fin::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
