#include <naivecgl/BndShape/BoundingBox.h>

Naive_NAMESPACE_BEGIN(bndshape);

Naive_Code BoundingBox::BoxFromPoints(const Naive_Point3dList &thePoints,
                                      Naive_Box &theBox) {
  Naive_Box aBox{};
  for (const auto &aPnt : thePoints) {
    aBox.Add(aPnt);
  }
  theBox = aBox;
  return Naive_Ok;
}

Naive_Code BoundingBox::OBBFromPoints(const Naive_Point3dList &thePoints,
                                      Naive_OBB &theOBB) {
  return Naive_Ok;
}

Naive_NAMESPACE_END(bndshape);
