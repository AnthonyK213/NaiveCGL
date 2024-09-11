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

void SpurEdgeVertex::Perform() {
  if (Status() != Naive_Code_initialized)
    return;

  if (!myVertex) {
    SetStatus(Naive_Code_null_arg_address);
    return;
  }

  Handle_Naive_Body aBody;
  if (!(aBody = Handle_Naive_Body::DownCast(myVertex->TopTopol()))) {
    SetStatus(Naive_Code_invalid_object);
    return;
  }

  Handle_Naive_Vertex aV = new Naive_Vertex;
  Handle_Naive_Edge aE = new Naive_Edge;

  aE->setVertex(myVertex, !myForward);
  aE->setVertex(aV, myForward);

  myNew.resize(2);
  MEV_E = aE;
  MEV_V = aV;

  Done();
}

Naive_NAMESPACE_END(eulerop);
