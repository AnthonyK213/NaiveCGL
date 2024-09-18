#include <naivecgl/BRepBuilderAPI/BuildSolidBlock.h>
#include <naivecgl/EulerOp/MakeBodyFaceVertex.h>
#include <naivecgl/EulerOp/MakeFaceEdge.h>
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
  Naive_List1<Handle_Naive_Vertex> aVerts{};
  Naive_List1<Handle_Naive_Edge> anEdges{};
  Naive_List1<Handle_Naive_Face> aFaces{};

  aVerts.reserve(8);
  anEdges.reserve(12);
  aFaces.reserve(6);

  euler_op::MakeBodyFaceVertex aMBFV{};
  myBody = aMBFV.NewBody();
  aFaces.push_back(aMBFV.NewFace());   /* F00 */
  aVerts.push_back(aMBFV.NewVertex()); /* V00 */

  euler_op::MakeFaceEdge aMFE(aFaces[0]->OuterLoop(), nullptr, nullptr);
  aFaces.push_back(aMFE.NewFace());  /* F01 */
  anEdges.push_back(aMFE.NewEdge()); /* E00 */

  /**
   * E01 ~ E07
   * V01 ~ V07
   */
  for (Naive_Integer i = 0; i < 7; ++i) {
  }

  /* F02, E08 */

  /* F03, E09 */

  /* F04, E10 */

  /* F05, E11 */

  Done();
}

Naive_NAMESPACE_END(brep_builder_api);
