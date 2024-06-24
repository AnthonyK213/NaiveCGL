#include <naivecgl/Math/Ax2.h>

Naive_NAMESPACE_BEGIN(math);

Ax2::Ax2() noexcept : myAxis(), myXDir(), myYDir() {}

Ax2::Ax2(const Naive_Pnt3d &theP, const Naive_Vec3d &theX,
         const Naive_Vec3d &theY) noexcept
    : myXDir(theX), myYDir(theY) {
  Naive_TODO;
}

Ax2::Ax2(const Naive_Pnt3d &theP, const Naive_Vec3d &theV) noexcept
    : myAxis(theP, theV) {
  Naive_TODO;
}

Ax2::Ax2(const Naive_Axis2_sf_t &theAx2) noexcept
    : myAxis(theAx2.location, theAx2.axis), myXDir(theAx2.ref_direction) {
  Naive_TODO;
}

Naive_Bool Ax2::IsValid() const {
  return myAxis.IsValid() && myXDir.IsValid() && myYDir.IsValid();
}

Naive_Bool Ax2::Dump(Naive_Axis2_sf_t &theAx2) const {
  return myAxis.Location().Dump(theAx2.location) &&
         myAxis.Direction().Dump(theAx2.axis) &&
         myXDir.Dump(theAx2.ref_direction);
}

Naive_NAMESPACE_END(math);
