#include <naivecgl/Math/Ax2.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(math);

Ax2::Ax2() noexcept : myAxis(), myXDir(), myYDir() {}

Ax2::Ax2(const Naive_Pnt3d &theP, const Naive_Vec3d &theX,
         const Naive_Vec3d &theY) noexcept
    : myAxis(), myXDir(theX.Normalized()), myYDir(theY.Normalized()) {
  Naive_Vec3d aZ = myXDir.Crossed(myYDir);
  myAxis.SetLocation(theP);
  myAxis.SetDirection(aZ);
  myYDir = aZ.Crossed(myXDir).Normalized();
}

Ax2::Ax2(const Naive_Pnt3d &theP, const Naive_Vec3d &theV) noexcept
    : myAxis(theP, theV) {
  if (!myAxis.IsValid())
    return;

  myXDir = Naive_Vec3d::XAxis();
  myYDir = myAxis.Direction().Crossed(myXDir).Normalized();

  if (!myYDir.IsValid()) {
    myXDir = Naive_Vec3d::YAxis();
    myYDir = myAxis.Direction().Crossed(myXDir).Normalized();
  }

  myXDir = myYDir.Crossed(myAxis.Direction()).Normalized();
}

Ax2::Ax2(const Naive_Axis2_sf_t &theAx2) noexcept
    : myAxis(theAx2.location, theAx2.axis), myXDir(theAx2.ref_direction) {
  myYDir = myAxis.Direction().Crossed(myXDir).Normalized();
  myXDir = myYDir.Crossed(myAxis.Direction()).Normalized();
}

Naive_Bool Ax2::IsValid() const {
  return myAxis.IsValid() && myXDir.IsValid() && myYDir.IsValid();
}

Naive_Bool Ax2::Transform(const Trsf3d &theTrsf) {
  if (IsValid() && theTrsf.IsValid()) {
    myAxis.Transform(theTrsf);
    myYDir.Transform(theTrsf);
    myXDir = myYDir.Crossed(myAxis.Direction());
    myXDir.Normalize();
    myYDir = myAxis.Direction().Crossed(myXDir);
    myYDir.Normalize();
    return Naive_True;
  }
  return Naive_False;
}

Ax2 Ax2::Transformed(const Trsf3d &theTrsf) const {
  Ax2 aCopy(*this);
  if (aCopy.Transform(theTrsf))
    return aCopy;
  return Unset();
}

const Ax2 &Ax2::Unset() {
  static Ax2 ax2{};
  return ax2;
}

Naive_Bool Ax2::Dump(Naive_Axis2_sf_t &theAx2) const {
  return myAxis.Location().Dump(theAx2.location) &&
         myAxis.Direction().Dump(theAx2.axis) &&
         myXDir.Dump(theAx2.ref_direction);
}

Naive_NAMESPACE_END(math);
