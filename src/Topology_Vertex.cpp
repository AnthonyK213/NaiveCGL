#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Vertex::Vertex() : Naive_Topol(), myTol(math::Precision::Epsilon0()) {}

Naive_Class Vertex::Class() const { return Naive_Class_vertex; }

Handle_Naive_Edge Vertex::ParentEdge() const {
  return Handle_Naive_Edge::DownCast(myParent);
}

Naive_NAMESPACE_END(topology);
