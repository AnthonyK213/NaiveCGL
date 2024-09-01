#include <naivecgl/EulerOp/SplitEdge.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

SplitEdge::SplitEdge()
    : MakeEdgeVertex(), myEdge(nullptr), myForward(Naive_True) {}

SplitEdge::SplitEdge(const Handle_Naive_Edge &theEdge,
                     const Naive_Bool theForward)
    : MakeEdgeVertex(), myEdge(theEdge), myForward(theForward) {
  Perform();
}

void SplitEdge::SetEdge(const Handle_Naive_Edge &theEdge) { myEdge = theEdge; }

void SplitEdge::SetForward(const Naive_Bool theForward) {
  myForward = theForward;
}

void SplitEdge::Perform() {
  if (Status() != Naive_Code_initialized)
    return;

  Naive_TODO;

  Done();
}

Naive_NAMESPACE_END(eulerop);
