#include <naivecgl/Geometry/Plane.h>

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

Naive_NAMESPACE_END(geometry);
