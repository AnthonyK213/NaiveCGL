#include <naivecgl/Math/Trsf3d.h>
#include <naivecgl/Math/Vec3d.h>

Naive_NAMESPACE_BEGIN(math);

Trsf3d::Trsf3d() {}

Trsf3d::Trsf3d(const Naive_Affine3d &theTrsf) : myAffine(theTrsf) {}

Trsf3d::Trsf3d(const Naive_Transform3d_sf_t &theTrsf) : myAffine() {
  for (Naive_Integer row = 0; row < 3; ++row) {
    for (Naive_Integer col = 0; col < 4; ++col) {
      myAffine(row, col) = theTrsf.matrix[row][col];
    }
  }
}

Naive_Bool Trsf3d::IsValid() const {
  return Vec3d(myAffine.translation()).IsValid();
}

Naive_Bool Trsf3d::IsIdentity(const Naive_Real theTol) const {
  return myAffine.matrix().isIdentity(theTol);
}

const Trsf3d &Trsf3d::Unset() {
  static Trsf3d aTrsf =
      Naive_Affine3d{::Eigen::Translation3d{Vec3d::Unset().XYZ()}};
  return aTrsf;
}

const Trsf3d &Trsf3d::Identity() {
  static Trsf3d aTrsf = Naive_Affine3d::Identity();
  return aTrsf;
}

Trsf3d Trsf3d::Translation(const Vec3d &theVec) {
  if (!theVec.IsValid())
    return Unset();
  Naive_Affine3d aTrsf(::Eigen::Translation3d(theVec.XYZ()));
  return {aTrsf};
}

Naive_NAMESPACE_END(math);
