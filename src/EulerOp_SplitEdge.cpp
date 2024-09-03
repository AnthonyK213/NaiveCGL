#include <naivecgl/EulerOp/SplitEdge.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

#define MEV_E (myNew[0])
#define MEV_V (myNew[1])

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

  if (!myEdge) {
    SetStatus(Naive_Code_null_arg_address);
    return;
  }

  Handle_Naive_Body aBody;
  if (!(aBody = Handle_Naive_Body::DownCast(myEdge->TopTopol()))) {
    SetStatus(Naive_Code_invalid_object);
    return;
  }

  Handle_Naive_Edge aE = new Naive_Edge();
  Handle_Naive_Vertex aV = new Naive_Vertex();

  if (myForward) {
    Handle_Naive_Vertex aVertex = myEdge->myVerts[0];
    myEdge->myVerts[0] = aV;
    aE->myVerts[0] = aVertex;
    aE->myVerts[1] = aV;

    /* TODO: Handle fins, loops... */
  } else {
  }

  aE->SetParent(aBody);
  aV->SetParent(aE);

  myNew.resize(2);
  MEV_E = aE;
  MEV_V = aV;

  Done();
}

Naive_NAMESPACE_END(eulerop);
