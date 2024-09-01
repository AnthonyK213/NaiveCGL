#include <naivecgl/BRepBuilderAPI/BuildSolidBlock.h>
#include <naivecgl/EulerOp/MakeBodyFaceVertex.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(brepbuilderapi);

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
  eulerop::MakeBodyFaceVertex aMBFV{};
  myBody = aMBFV.NewBody();

  Done();
}

Naive_NAMESPACE_END(brepbuilderapi);
