#include <naivecgl/BRepBuilderAPI/BuildSolidBlock.h>
#include <naivecgl/EulerOp/MakeBodyFaceVertex.h>
#include <naivecgl/EulerOp/MakeFaceEdge.h>
#include <naivecgl/EulerOp/SplitEdge.h>
#include <naivecgl/Geometry/CartesianPoint3d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Topology/Body.h>
#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(brep_builder_api);

BuildSolidBlock::BuildSolidBlock() : myAx2(), myX(0.), myY(0.), myZ(0.) {}

BuildSolidBlock::BuildSolidBlock(const Naive_Ax2 &theAx2, const Naive_Real theX,
                                 const Naive_Real theY, const Naive_Real theZ) {
  Init(theAx2, theX, theY, theZ);
}

void BuildSolidBlock::Init(const Naive_Ax2 &theAx2, const Naive_Real theX,
                           const Naive_Real theY, const Naive_Real theZ) {
  myAx2 = theAx2;
  myX = theX;
  myY = theY;
  myZ = theZ;

  Build();
}

void BuildSolidBlock::Build() {
  if (!myAx2.IsValid() || myX <= 0. || myY <= 0. || myZ <= 0.) {
    SetStatus(Naive_Code_invalid_value);
    return;
  }

  Naive_List1<Handle_Naive_Vertex> aVs{};
  Naive_List1<Handle_Naive_Edge> aEs{};
  Naive_List1<Handle_Naive_Face> aFs{};

  aVs.reserve(8);
  aEs.reserve(12);
  aFs.reserve(6);

  /* F00, V00 */
  euler_op::MakeBodyFaceVertex aMBFV{};
  myBody = aMBFV.NewBody();
  aFs.push_back(aMBFV.NewFace());
  aVs.push_back(aMBFV.NewVertex());

  /* F01, E00 */
  euler_op::MakeFaceEdge aMFE(aFs[0]->OuterLoop(), nullptr, nullptr);
  aFs.push_back(aMFE.NewFace());
  aEs.push_back(aMFE.NewEdge());

  /**
   * E01 ~ E07
   * V01 ~ V07
   */

  euler_op::SplitEdge aSplit{};
  aSplit.SetEdge(aEs[0]);
  aSplit.SetForward(Naive_True);

  for (Naive_Integer i = 0; i < 7; ++i) {
    aSplit.Reset();
    aSplit.Perform();
    aEs.push_back(aSplit.NewEdge());
    aVs.push_back(aSplit.NewVertex());
  }

  aMFE.SetLoop(aFs[0]->OuterLoop());

  /* F02, E08 */
  aMFE.Reset();
  aMFE.SetFin1(aEs[0]->ForwardFin());
  aMFE.SetFin2(aEs[5]->ForwardFin());
  aMFE.Perform();
  aFs.push_back(aMFE.NewFace());
  aEs.push_back(aMFE.NewEdge());

  /* F03, E09 */
  aMFE.Reset();
  aMFE.SetFin1(aEs[1]->ForwardFin());
  aMFE.SetFin2(aEs[4]->ForwardFin());
  aMFE.Perform();
  aFs.push_back(aMFE.NewFace());
  aEs.push_back(aMFE.NewEdge());

  aMFE.SetLoop(aFs[1]->OuterLoop());

  /* F04, E10 */
  aMFE.Reset();
  aMFE.SetFin1(aEs[2]->BackwardFin());
  aMFE.SetFin2(aEs[5]->BackwardFin());
  aMFE.Perform();
  aFs.push_back(aMFE.NewFace());
  aEs.push_back(aMFE.NewEdge());

  /* F05, E11 */
  aMFE.Reset();
  aMFE.SetFin1(aEs[1]->BackwardFin());
  aMFE.SetFin2(aEs[6]->BackwardFin());
  aMFE.Perform();
  aFs.push_back(aMFE.NewFace());
  aEs.push_back(aMFE.NewEdge());

  /* TODO: Attach geometry. */

  Naive_Real aHX = myX / 2., aHY = myY / 2.;

  Naive_Pnt3dList1 aPnts{
      {aHX, -aHY, myZ}, {aHX, -aHY, 0.}, {-aHX, -aHY, 0.}, {-aHX, -aHY, myZ},
      {-aHX, aHY, myZ}, {-aHX, aHY, 0.}, {aHX, aHY, 0.},   {aHX, aHY, myZ},
  };

  for (Naive_Integer i = 0; i < 8; ++i) {
    Naive_Pnt3d aPnt = myAx2.ToGlobal(aPnts[i]);
    Handle_Naive_CartesianPoint3d aGeom = new Naive_CartesianPoint3d(aPnt);
    aVs[i]->AttachPoint(aGeom);
  }

  Done();
}

Naive_NAMESPACE_END(brep_builder_api);
