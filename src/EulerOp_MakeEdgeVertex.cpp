#include <naivecgl/EulerOp/MakeEdgeVertex.h>
#include <naivecgl/EulerOp/TEV.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(euler_op);

#define MEV_E (myNew[0])
#define MEV_V (myNew[1])

Naive_IMPLEMENT_EO(MakeEdgeVertex, 1, 1, 0, 0, 0, 0);

MakeEdgeVertex::MakeEdgeVertex() : Operator() {}

Handle_Naive_Vertex MakeEdgeVertex::NewVertex() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Vertex::DownCast(MEV_V);
}

Handle_Naive_Edge MakeEdgeVertex::NewEdge() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Edge::DownCast(MEV_E);
}

Naive_NAMESPACE_END(euler_op);
