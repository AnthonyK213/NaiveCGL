#include <naivecgl/EulerOp/MakeFaceEdge.h>
#include <naivecgl/EulerOp/TEV.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

#define MEV_F (myNew[0])
#define MEV_E (myNew[1])

MakeFaceEdge::MakeFaceEdge() {}

MakeFaceEdge::MakeFaceEdge(const Handle_Naive_Loop &theLoop,
                           const Handle_Naive_Fin &theFin1,
                           const Handle_Naive_Fin &theFin2)
    : myLoop(theLoop), myFin1(theFin1), myFin2(theFin2) {
  Perform();
}

void MakeFaceEdge::SetLoop(const Naive_Handle<topology::Loop> &theLoop) {
  myLoop = theLoop;
}

void MakeFaceEdge::SetFin1(const Naive_Handle<topology::Fin> &theFin) {
  myFin1 = theFin;
}

void MakeFaceEdge::SetFin2(const Naive_Handle<topology::Fin> &theFin) {
  myFin2 = theFin;
}

Handle_Naive_Face MakeFaceEdge::NewFace() const {
  return Handle_Naive_Face::DownCast(MEV_F);
}

Handle_Naive_Edge MakeFaceEdge::NewEdge() const {
  return Handle_Naive_Edge::DownCast(MEV_E);
}

Naive_Code MakeFaceEdge::CheckParams() const {
  if (!myLoop)
    return Naive_Code_null_arg_address;

  if (!myFin1 && myFin2)
    return Naive_Code_null_arg_address;

  if (myFin1 && !myFin2)
    return Naive_Code_null_arg_address;

  if (myFin1 && myFin1->ParentLoop() != myLoop)
    return Naive_Code_fin_not_in_loop;

  if (myFin2 && myFin2->ParentLoop() != myLoop)
    return Naive_Code_fin_not_in_loop;

  return Naive_Code_ok;
}

Naive_Code MakeFaceEdge::PerformInternal() {
  if (!myFin1 && !myFin2) {
    Naive_Face *aParentFace = myLoop->ParentFace();
    if (!aParentFace)
      return Naive_Code_err;
    Naive_Shell *aShell = aParentFace->ParentShell();
    if (!aShell)
      return Naive_Code_err;
    Handle_Naive_Vertex aVert = aShell->GetVertex();
    if (!aVert)
      return Naive_Code_err;
    Naive_Body *aBody = dynamic_cast<Naive_Body *>(aShell->TopTopol());
    if (!aBody)
      return Naive_Code_err;

    Handle_Naive_Edge anEdge = new Naive_Edge(aVert, aVert);
    Handle_Naive_Face aFace = new Naive_Face;

    myLoop->AppendFin(anEdge->ForwardFin().get());
    aFace->myLoops.front()->AppendFin(anEdge->BackwardFin().get());
    aFace->SetParent(aShell);
    anEdge->SetParent(aBody);
    aFace->myPrev = aParentFace;
    aParentFace->myNext = anEdge;

    myNew.resize(2);
    MEV_F = aFace;
    MEV_E = anEdge;
  } else {
  }

  return Naive_Code_ok;
}

Naive_IMPLEMENT_EO(MakeFaceEdge, 0, 1, 1, 0, 0, 0);

Naive_NAMESPACE_END(eulerop);
