#include <naivecgl/Math/Ax1.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(math);

Ax1::Ax1() noexcept : myLoc(), myDir() {}

Ax1::Ax1(const Naive_Pnt3d &theP, const Naive_Vec3d &theV) noexcept
    : myLoc(theP), myDir(theV.Normalized()) {}

Ax1::Ax1(const Naive_Axis1_sf_t &theAx1) noexcept
    : myLoc(theAx1.location), myDir(Naive_Vec3d(theAx1.axis).Normalized()) {}

const Ax1 &Ax1::Unset() {
  static Ax1 anAx1{};
  return anAx1;
}

Naive_Bool Ax1::IsValid() const { return myLoc.IsValid() && myDir.IsValid(); }

Naive_Bool Ax1::Transform(const Trsf3d &theTrsf) {
  if (IsValid() && theTrsf.IsValid()) {
    myLoc.Transform(theTrsf);
    myDir.Transform(theTrsf);
    return Naive_True;
  }
  return Naive_False;
}

Ax1 Ax1::Transformed(const Trsf3d &theTrsf) const {
  Ax1 aCopy(*this);
  if (aCopy.Transform(theTrsf))
    return aCopy;
  return Unset();
}

Naive_Bool Ax1::Dump(Naive_Axis1_sf_t &theAx1) const {
  return myLoc.Dump(theAx1.location) && myDir.Dump(theAx1.axis);
}

Naive_NAMESPACE_END(math);
