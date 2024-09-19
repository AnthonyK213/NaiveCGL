#include <naivecgl/Math/Box.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Region.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Shell);

Shell::Shell()
    : myRegion(nullptr), myVertex(nullptr), myFace(nullptr), myEdge(nullptr) {}

Naive_Topol *Shell::Parent() const { return myRegion; }

Naive_Region *Shell::ParentRegion() const { return myRegion; }

void Shell::GetBox(Naive_Box &theBox) {}

Naive_Code Shell::SetVertex(const Handle_Naive_Vertex &theVert) {
  if (!theVert) {
    myVertex = nullptr;
    return Naive_Code_ok;
  }

  Naive_Topol *aParent = theVert->Parent();

  if (aParent == this)
    return Naive_Code_ok;

  theVert->SetParent(this);
  theVert->myPrev = nullptr;
  theVert->myNext = nullptr;
  myVertex = theVert;

  return Naive_Code_ok;
}

Naive_Code Shell::AppendFace(const Handle_Naive_Face &theFace) {
  if (!theFace)
    return Naive_Code_null_arg_address;

  Naive_Shell *aShell = theFace->ParentShell();

  if (aShell == this)
    return Naive_Code_ok;

  theFace->SetParent(this);
  theFace->myPrev = nullptr;
  theFace->myNext = myFace;
  if (myFace)
    myFace->myPrev = theFace.get();
  myFace = theFace;

  return Naive_Code_ok;
}

Naive_LinkedList<Naive_Handle<Face>> Shell::GetFaces() const {
  Naive_LinkedList<Handle_Naive_Face> aResult{};

  Handle_Naive_Face aCurr = myFace;
  while (aCurr) {
    aResult.push_back(aCurr);
    aCurr = aCurr->myNext;
  }

  return aResult;
}

void Shell::SetParent(Naive_Topol *theParent) {
  myRegion = dynamic_cast<Naive_Region *>(theParent);
}

Naive_NAMESPACE_END(topology);
