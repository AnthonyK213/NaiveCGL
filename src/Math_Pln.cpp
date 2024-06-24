#include <naivecgl/Math/Pln.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(math);

Pln::Pln() : myPos() {}

Pln::Pln(const Naive_Ax2 &theAx2) : myPos(theAx2) {}

Pln::Pln(const Naive_Pnt3d &theP, const Naive_Vec3d &theXAxis,
         const Naive_Vec3d &theYAxis)
    : myPos(theP, theXAxis, theYAxis) {}

Pln::Pln(const Naive_Pnt3d &theP, const Naive_Vec3d &theN)
    : myPos(theP, theN) {}

Pln::Pln(const Naive_Plane_sf_t &thePln) : myPos(thePln.basis_set) {}

Naive_Bool Pln::IsValid() const { return myPos.IsValid(); }

Naive_Real Pln::Distance(const Naive_Pnt3d &theP) const {
  Naive_Real aDist = (Axis().X() * (theP.X() - Location().X()) +
                      Axis().Y() * (theP.Y() - Location().Y()) +
                      Axis().Z() * (theP.Z() - Location().Z()));

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

Naive_Bool Pln::Transform(const Naive_Trsf3d &theTrsf) { Naive_TODO; }

Pln Pln::Transformed(const Naive_Trsf3d &theTrsf) const { Naive_TODO; }

Naive_Bool Pln::Dump(Naive_Plane_sf_t &thePln) const {
  return myPos.Dump(thePln.basis_set);
}

Naive_Bool Pln::Orient(const Pln &thePln1, const Pln &thePln2,
                       Trsf3d &theTrsf) {
  if (!thePln1.IsValid() || !thePln2.IsValid())
    return Naive_False;

  Naive_Affine3d aT1{};
  aT1.setIdentity();
  Naive_Matrix3d aR1{};
  aR1.col(0) = thePln1.XAxis().XYZ();
  aR1.col(1) = thePln1.YAxis().XYZ();
  aR1.col(2) = thePln1.Axis().XYZ();
  aT1.rotate(aR1);
  aT1.translation() = thePln1.Location().XYZ();

  Naive_Affine3d aT2{};
  aT2.setIdentity();
  Naive_Matrix3d aR2{};
  aR2.col(0) = thePln2.XAxis().XYZ();
  aR2.col(1) = thePln2.YAxis().XYZ();
  aR2.col(2) = thePln2.Axis().XYZ();
  aT2.rotate(aR2);
  aT2.translation() = thePln2.Location().XYZ();

  theTrsf = {aT2 * aT1.inverse()};
  return Naive_True;
}

Naive_NAMESPACE_END(math);
