#include <naivecgl/EulerOp/SpurEdgeVertex.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

#define MEV_E (myNew[0])
#define MEV_V (myNew[1])

SpurEdgeVertex::SpurEdgeVertex() : myVertex(nullptr), myForward(Naive_True) {}

SpurEdgeVertex::SpurEdgeVertex(const Naive_Handle<topology::Vertex> &theVert,
                               const Naive_Bool theForward)
    : myVertex(theVert), myForward(theForward) {}

void SpurEdgeVertex::SetVertex(const Naive_Handle<topology::Vertex> &theVert) {
  myVertex = theVert;
}

void SpurEdgeVertex::SetForward(const Naive_Bool theForward) {
  myForward = theForward;
}

Naive_Code SpurEdgeVertex::CheckParams() const {
  if (!myVertex)
    return Naive_Code_null_arg_address;

  return Naive_Code_ok;
}

Naive_Code SpurEdgeVertex::PerformInternal() {
  Handle_Naive_Body aBody;

  if (!(aBody = Handle_Naive_Body::DownCast(myVertex->TopTopol())))
    return Naive_Code_invalid_object;

  Handle_Naive_Vertex aV = new Naive_Vertex;
  Handle_Naive_Edge aE = new Naive_Edge;

  aE->setVertex(myVertex, !myForward);
  aE->setVertex(aV, myForward);

  myNew.resize(2);
  MEV_E = aE;
  MEV_V = aV;

  return Naive_Code_ok;
}

Naive_NAMESPACE_END(eulerop);
