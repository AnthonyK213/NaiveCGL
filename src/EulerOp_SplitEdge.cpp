#include <naivecgl/EulerOp/SplitEdge.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

#define MEV_E (myNew[0])
#define MEV_V (myNew[1])

SplitEdge::SplitEdge() : myEdge(nullptr), myForward(Naive_True) {}

SplitEdge::SplitEdge(const Handle_Naive_Edge &theEdge,
                     const Naive_Bool theForward)
    : myEdge(theEdge), myForward(theForward) {
  Perform();
}

void SplitEdge::SetEdge(const Handle_Naive_Edge &theEdge) { myEdge = theEdge; }

void SplitEdge::SetForward(const Naive_Bool theForward) {
  myForward = theForward;
}

Naive_Code SplitEdge::CheckParams() const {
  if (!myEdge)
    return Naive_Code_null_arg_address;

  if (!myEdge->IsManifold())
    return Naive_Code_edge_not_manifold;

  if (!myEdge->GetVertex(0)->IsManifold() ||
      !myEdge->GetVertex(1)->IsManifold())
    return Naive_Code_vertex_not_manifold;

  return Naive_Code_ok;
}

Naive_Code SplitEdge::PerformInternal() {
  Handle_Naive_Body aBody;

  if (!(aBody = Handle_Naive_Body::DownCast(myEdge->TopTopol())))
    return Naive_Code_invalid_object;

  Handle_Naive_Vertex aV = new Naive_Vertex;
  Handle_Naive_Edge aE = new Naive_Edge;
  Handle_Naive_Vertex aToSplit = myEdge->GetVertex(myForward);

  myEdge->setVertex(aV, myForward);
  aE->setVertex(aToSplit, myForward);
  aE->setVertex(aV, !myForward);

  aE->SetParent(myEdge->Parent());
  aV->SetParent(aBody.get());

  Naive_Fin *aOld, *aNew;

  if (myEdge->ForwardFin()->ParentLoop()) {
    aOld = myEdge->ForwardFin().get();
    aNew = aE->ForwardFin().get();

    if (myForward) {
      aNew->myPrev = aOld;
      aNew->myNext = aOld->Next();
      aOld->myNext = aNew;
    } else {
      aNew->myNext = aOld;
      aNew->myPrev = aOld->Prev();
      aOld->myPrev = aNew;
    }

    aNew->myLoop = aOld->ParentLoop();
  }

  if (myEdge->BackwardFin()->ParentLoop()) {
    aOld = myEdge->BackwardFin().get();
    aNew = aE->BackwardFin().get();

    if (myForward) {
      aNew->myNext = aOld;
      aNew->myPrev = aOld->Prev();
      aOld->myPrev = aNew;
    } else {
      aNew->myPrev = aOld;
      aNew->myNext = aOld->Next();
      aOld->myNext = aNew;
    }

    aNew->myLoop = aOld->ParentLoop();
  }

  myNew.resize(2);
  MEV_E = aE;
  MEV_V = aV;

  return Naive_Code_ok;
}

Naive_NAMESPACE_END(eulerop);
