#include <naivecgl/EulerOp/MakeBodyFaceVertex.h>
#include <naivecgl/EulerOp/TEV.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(eulerop);

Naive_IMPLEMENT_EO(MakeBodyFaceVertex, 1, 0, 1, 0, 0, 1);

#define MBFV_B (myNew[0])
#define MBFV_S (myNew[1])
#define MBFV_F (myNew[2])
#define MBFV_V (myNew[3])

MakeBodyFaceVertex::MakeBodyFaceVertex() : Operator() { Perform(); }

void MakeBodyFaceVertex::Perform() {
  if (Status() != Naive_Code_initialized)
    return;

  Handle_Naive_Body aB = new Naive_Body();
  Handle_Naive_Shell aS = new Naive_Shell();
  Handle_Naive_Face aF = new Naive_Face();
  Handle_Naive_Vertex aV = new Naive_Vertex();

  aB->myShells.push_back(aS);
  aB->myFaces.push_back(aF);
  aB->myVertices.push_back(aV);

  aS->myFaces.push_back(aF);

  aB->SetParent(nullptr);
  aS->SetParent(aB);
  aF->SetParent(aS);
  aV->SetParent(aB);

  myNew.resize(4);
  MBFV_B = aB;
  MBFV_S = aS;
  MBFV_F = aF;
  MBFV_V = aV;

  Done();
}

Handle_Naive_Body MakeBodyFaceVertex::NewBody() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Body::DownCast(MBFV_B);
}

Handle_Naive_Shell MakeBodyFaceVertex::NewShell() const {
  if (!IsDone())
    return nullptr;
  return Handle_Naive_Shell::DownCast(MBFV_S);
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
