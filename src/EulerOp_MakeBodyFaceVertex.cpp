#include <naivecgl/EulerOp/MakeBodyFaceVertex.h>
#include <naivecgl/EulerOp/TEV.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Region.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

Naive_IMPLEMENT_EO(MakeBodyFaceVertex, 1, 0, 1, 0, 0, 1);

#define MBFV_B (myNew[0])
#define MBFV_F (myNew[1])
#define MBFV_V (myNew[2])

MakeBodyFaceVertex::MakeBodyFaceVertex() : Operator() { Perform(); }

void MakeBodyFaceVertex::Perform() {
  if (Status() != Naive_Code_initialized)
    return;

  Handle_Naive_Body aB = new Naive_Body();
  Handle_Naive_Region aR = new Naive_Region();
  Handle_Naive_Shell aS = new Naive_Shell();
  Handle_Naive_Face aF = new Naive_Face();
  Handle_Naive_Vertex aV = new Naive_Vertex();

  aB->myRegion = aR;
  aR->myShells.push_back(aS);
  aS->myFace = aF;
  aS->myVertex = aV;

  aB->SetParent(nullptr);
  aR->SetParent(aB.get());
  aS->SetParent(aR.get());
  aF->SetParent(aS.get());
  aV->SetParent(aS.get());

  myNew.resize(3);
  MBFV_B = aB;
  MBFV_F = aF;
  MBFV_V = aV;

  Done();
}

Handle_Naive_Body MakeBodyFaceVertex::NewBody() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Body::DownCast(MBFV_B);
}

Handle_Naive_Face MakeBodyFaceVertex::NewFace() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Face::DownCast(MBFV_F);
}

Handle_Naive_Vertex MakeBodyFaceVertex::NewVertex() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Vertex::DownCast(MBFV_V);
}

Naive_NAMESPACE_END(eulerop);
