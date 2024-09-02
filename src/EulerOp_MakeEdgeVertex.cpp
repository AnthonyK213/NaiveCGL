#include <naivecgl/EulerOp/MakeEdgeVertex.h>
#include <naivecgl/EulerOp/TEV.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

Naive_IMPLEMENT_EO(MakeEdgeVertex, 1, 1, 0, 0, 0, 0);

MakeEdgeVertex::MakeEdgeVertex() : Operator() {}

Handle_Naive_Vertex MakeEdgeVertex::NewVertex() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Vertex::DownCast(myNew[0]);
}

Handle_Naive_Edge MakeEdgeVertex::NewEdge() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Edge::DownCast(myNew[1]);
}

Naive_NAMESPACE_END(eulerop);
