#include <naivecgl/Geometry/Plane.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Plane);

Plane::Plane() {}

Plane::Plane(const Naive_Pln &thePln) { myPos = thePln.Ax2(); }

Naive_Bool Plane::IsValid() const { return myPos.IsValid(); }

Handle_Naive_Geometry Plane::Clone() const { return new Plane(myPos); }

Naive_Pnt3d Plane::PointAt(const Naive_Real theU, const Naive_Real theV) const {
  if (!IsValid())
    return Naive_Pnt3d::Unset();
  return myPos.Location() + theU * myPos.XDirection() +
         theV * myPos.YDirection();
}

Naive_Code Plane::Evaluate(const Naive_Real theU, const Naive_Real theV,
                           const Naive_Integer theN,
                           Naive_Vec3dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  if (theN < 0)
    return Naive_Code_value_out_of_range;

  Naive_Integer aN = (theN + 1) * (theN + 2) / 2;
  theD.resize(aN, Naive_Vec3d::Zero());

  theD[0].ChangeXYZ() = PointAt(theU, theV).XYZ();

  if (theN >= 1) {
    theD[1].ChangeXYZ() = myPos.XDirection().XYZ();
    theD[2].ChangeXYZ() = myPos.YDirection().XYZ();
  }

  return Naive_Code_ok;
}

Naive_Real Plane::Distance(const Naive_Pnt3d &theP) const {
  Naive_Pln aPln{myPos};
  return aPln.Distance(theP);
}

Naive_Bool Plane::Bounds(Naive_Real &theU0, Naive_Real &theU1,
                         Naive_Real &theV0, Naive_Real &theV1) const {
  if (!IsValid())
    return Naive_False;

  theU0 = -math::Constant::Infinite();
  theU1 = math::Constant::Infinite();
  theV0 = -math::Constant::Infinite();
  theV1 = math::Constant::Infinite();

  return Naive_True;
}

Naive_Bool Plane::IsUClosed() const { return Naive_False; }

Naive_Bool Plane::IsVClosed() const { return Naive_False; }

Naive_Bool Plane::IsUPeriodic() const { return Naive_False; }

Naive_Bool Plane::IsVPeriodic() const { return Naive_False; }

Naive_Real Plane::UPeriod() const { return math::Constant::UnsetReal(); }

Naive_Real Plane::VPeriod() const { return math::Constant::UnsetReal(); }

Naive_NAMESPACE_END(geometry);
