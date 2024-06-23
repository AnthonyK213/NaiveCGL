#include <naivecgl/BndShape/BoundingBox.h>

Naive_NAMESPACE_BEGIN(bndshape);

Naive_Code BoundingBox::BoxFromPoints(const Naive_Pnt3dList1 &thePoints,
                                      Naive_Box &theBox) {
  Naive_Box aBox{};
  for (const auto &aPnt : thePoints) {
    aBox.Add(aPnt);
  }
  theBox = aBox;
  return Naive_Code_ok;
}

Naive_Code BoundingBox::OBBFromPoints(const Naive_Pnt3dList1 &thePoints,
                                      Naive_OBB &theOBB) {
  return Naive_Code_ok;
}

Naive_NAMESPACE_END(bndshape);
