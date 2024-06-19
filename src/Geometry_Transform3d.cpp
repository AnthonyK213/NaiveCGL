#include <naivecgl/Geometry/Transform3d.h>
#include <naivecgl/Geometry/Vector3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Transform3d::Transform3d() {}

Transform3d::Transform3d(const Naive_Trsf &theTrsf) : myTrsf(theTrsf) {}

Transform3d::Transform3d(const Naive_Transform3d_sf_t &theTrsf) : myTrsf() {
  for (Naive_Integer row = 0; row < 3; ++row) {
    for (Naive_Integer col = 0; col < 4; ++col) {
      myTrsf(row, col) = theTrsf.matrix[row][col];
    }
  }
}

Naive_Bool Transform3d::IsValid() const {
  return Vector3d(myTrsf.translation()).IsValid();
}

Naive_Bool Transform3d::IsIdentity(const Naive_Real theTol) const {
  return myTrsf.matrix().isIdentity(theTol);
}

const Transform3d &Transform3d::Unset() {
  static Transform3d aTrsf =
      Naive_Trsf{::Eigen::Translation3d{Vector3d::Unset().XYZ()}};
  return aTrsf;
}

const Transform3d &Transform3d::Identity() {
  static Transform3d aTrsf = Naive_Trsf::Identity();
  return aTrsf;
}

Transform3d Transform3d::Translation(const Vector3d &theVec) {
  if (!theVec.IsValid())
    return Unset();
  Naive_Trsf aTrsf(::Eigen::Translation3d(theVec.XYZ()));
  return {aTrsf};
}

Naive_NAMESPACE_END(geometry);
