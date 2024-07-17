#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Edge);

Edge::Edge() : Naive_Topol(), myTol(math::Precision::Epsilon0()) {}

Handle_Naive_Fin Edge::ParentFin() const {
  return Handle_Naive_Fin::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
