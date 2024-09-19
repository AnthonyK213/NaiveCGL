#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Region.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Body);

Body::Body()
    : myBody(nullptr), myPrev(nullptr), myNext(nullptr), myChild(nullptr),
      myRegion(nullptr), myEdge(nullptr), myVertex(nullptr) {}

Naive_Topol *Body::Parent() const { return myBody; }

Naive_Body *Body::ParentBody() const { return myBody; }

void Body::GetBox(Naive_Box &theBox) {}

void Body::SetParent(Naive_Topol *theParent) {
  myBody = dynamic_cast<Naive_Body *>(theParent);
}

Naive_Code Body::AppendVertex(const Handle_Naive_Vertex &theVert) {
  if (!theVert)
    return Naive_Code_null_arg_address;

  Naive_Topol *aParent = theVert->Parent();

  if (aParent == this)
    return Naive_Code_ok;

  if (aParent) {
    Naive_Shell *aShell = dynamic_cast<Naive_Shell *>(aParent);
    if (aShell) {
      aShell->myVertex = nullptr;
    }
  }

  theVert->SetParent(this);
  theVert->myPrev = nullptr;
  theVert->myNext = myVertex;
  if (myVertex)
    myVertex->myPrev = theVert.get();
  myVertex = theVert;

  return Naive_Code_ok;
}

Naive_Code Body::AppendEdge(const Handle_Naive_Edge &theEdge) {
  if (!theEdge)
    return Naive_Code_null_arg_address;

  Naive_Topol *aParent = theEdge->Parent();

  if (aParent == this)
    return Naive_Code_ok;

  if (aParent) {
    /* TODO: Reomve the edge from the old owner. */
  }

  theEdge->SetParent(this);
  theEdge->myPrev = nullptr;
  theEdge->myNext = myEdge;
  if (myEdge)
    myEdge->myPrev = theEdge.get();
  myEdge = theEdge;

  AppendVertex(myEdge->GetVertex(Naive_False));
  AppendVertex(myEdge->GetVertex(Naive_True));

  return Naive_Code_ok;
}

Naive_LinkedList<Handle_Naive_Face> Body::GetFaces() const {
  Naive_LinkedList<Handle_Naive_Face> aResult{};

  Handle_Naive_Region aCurr = myRegion;
  while (aCurr) {
    const Naive_LinkedList<Handle_Naive_Shell> &aShells = aCurr->GetShells();
    for (const Handle_Naive_Shell &aShell : aShells) {
      aResult.splice(aResult.end(), aShell->GetFaces());
    }
    aCurr = aCurr->myNext;
  }

  return aResult;
}

Naive_LinkedList<Handle_Naive_Edge> Body::GetEdges() const {
  Naive_LinkedList<Handle_Naive_Edge> aResult{};

  Handle_Naive_Edge aCurr = myEdge;
  while (aCurr) {
    aResult.push_back(aCurr);
    aCurr = aCurr->myNext;
  }

  return aResult;
}

Naive_LinkedList<Handle_Naive_Vertex> Body::GetVertices() const {
  Naive_LinkedList<Handle_Naive_Vertex> aResult{};

  Handle_Naive_Vertex aCurr = myVertex;
  while (aCurr) {
    aResult.push_back(aCurr);
    aCurr = aCurr->myNext;
  }

  return aResult;
}

Naive_NAMESPACE_END(topology);
