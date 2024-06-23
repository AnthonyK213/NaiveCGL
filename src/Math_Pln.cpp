#include <naivecgl/Math/Pln.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(math);

Pln::Pln() { initInvalid(); }

Pln::Pln(const Naive_Pnt3d &theP, const Naive_Vec3d &theXAxis,
         const Naive_Vec3d &theYAxis)
    : myLocation(theP), myXAxis(theXAxis), myYAxis(theYAxis) {
  if (!initByXY())
    initInvalid();
}

Pln::Pln(const Naive_Pnt3d &theP, const Naive_Vec3d &theN)
    : myLocation(theP), myZAxis(theN) {
  if (!myZAxis.Normalize()) {
    initInvalid();
    return;
  }

  myXAxis = Naive_Vec3d::YAxis().Crossed(myZAxis);
  if (!myXAxis.Normalize()) {
    myXAxis = Naive_Vec3d::XAxis().Crossed(myZAxis);
  }

  myYAxis = myZAxis.Crossed(myXAxis);
  myYAxis.Normalize();
}

Pln::Pln(const Naive_Plane_sf_t &thePln)
    : myLocation(thePln.basis_set.location),
      myXAxis(thePln.basis_set.ref_direction), myZAxis(thePln.basis_set.axis) {
  if (!initByZX())
    initInvalid();
}

Naive_Bool Pln::IsValid() const {
  return myLocation.IsValid() && myXAxis.IsValid() && !myXAxis.IsZero() &&
         myYAxis.IsValid() && !myYAxis.IsZero() && myZAxis.IsValid() &&
         !myZAxis.IsZero();
}

Naive_Real Pln::Distance(const Naive_Pnt3d &theP) const {
  Naive_Real aDist = (myZAxis.X() * (theP.X() - myLocation.X()) +
                      myZAxis.Y() * (theP.Y() - myLocation.Y()) +
                      myZAxis.Z() * (theP.Z() - myLocation.Z()));

  if (aDist < 0)
    aDist = -aDist;

  return aDist;
}

const Pln &Pln::Unset() {
  static Pln aPlane{};
  return aPlane;
}

const Pln &Pln::WorldXY() {
  static Pln aPln{Naive_Pnt3d::Origin(), Naive_Vec3d::XAxis(),
                  Naive_Vec3d::YAxis()};
  return aPln;
}

const Pln &Pln::WorldYZ() {
  static Pln aPln{Naive_Pnt3d::Origin(), Naive_Vec3d::YAxis(),
                  Naive_Vec3d::ZAxis()};
  return aPln;
}

const Pln &Pln::WorldZX() {
  static Pln aPln{Naive_Pnt3d::Origin(), Naive_Vec3d::ZAxis(),
                  Naive_Vec3d::XAxis()};
  return aPln;
}

Naive_Bool Pln::Transform(const Naive_Trsf3d &theTrsf) {
  if (!myLocation.Transform(theTrsf) || !myXAxis.Transform(theTrsf) ||
      !myYAxis.Transform(theTrsf))
    return Naive_False;

  initByXY();
  return Naive_True;
}

Pln Pln::Transformed(const Naive_Trsf3d &theTrsf) const {
  Pln aPlane(*this);
  if (aPlane.Transform(theTrsf))
    return aPlane;
  return Unset();
}

Naive_Bool Pln::Dump(Naive_Plane_sf_t &thePln) const {
  if (!IsValid())
    return Naive_False;

  return myLocation.Dump(thePln.basis_set.location) &&
         myZAxis.Dump(thePln.basis_set.axis) &&
         myXAxis.Dump(thePln.basis_set.ref_direction);
}

Naive_Bool Pln::Orient(const Pln &thePln, Naive_Trsf3d &theTrsf) const {
  if (!IsValid() || !thePln.IsValid())
    return Naive_False;

  Naive_Affine3d aT1{};
  aT1.setIdentity();
  Naive_Matrix3d aR1{};
  aR1.col(0) = myXAxis.XYZ();
  aR1.col(1) = myYAxis.XYZ();
  aR1.col(2) = myZAxis.XYZ();
  aT1.rotate(aR1);
  aT1.translation() = myLocation.XYZ();

  Naive_Affine3d aT2{};
  aT2.setIdentity();
  Naive_Matrix3d aR2{};
  aR2.col(0) = thePln.myXAxis.XYZ();
  aR2.col(1) = thePln.myYAxis.XYZ();
  aR2.col(2) = thePln.myZAxis.XYZ();
  aT2.rotate(aR2);
  aT2.translation() = thePln.myLocation.XYZ();

  theTrsf = {aT2 * aT1.inverse()};
  return Naive_True;
}

void Pln::initInvalid() {
  myLocation = Naive_Pnt3d::Unset();
  myXAxis = Naive_Vec3d::Unset();
  myYAxis = Naive_Vec3d::Unset();
  myZAxis = Naive_Vec3d::Unset();
}

Naive_Bool Pln::initByXY() {
  if (!myXAxis.Normalize())
    return Naive_False;

  myZAxis = myXAxis.Crossed(myYAxis);
  if (!myZAxis.Normalize())
    return Naive_False;

  myYAxis = myZAxis.Crossed(myXAxis);
  if (!myYAxis.Normalize())
    return Naive_False;

  return Naive_True;
}

Naive_Bool Pln::initByZX() {
  if (!myZAxis.Normalize())
    return Naive_False;

  myYAxis = myZAxis.Crossed(myXAxis);
  if (!myYAxis.Normalize())
    return Naive_False;

  myXAxis = myYAxis.Crossed(myZAxis);
  if (!myXAxis.Normalize())
    return Naive_False;

  return Naive_True;
}

Naive_NAMESPACE_END(math);
