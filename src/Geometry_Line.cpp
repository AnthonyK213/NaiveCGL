#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Line);

Line::Line(const Naive_Pnt3d &theFrom, const Naive_Pnt3d &theTo)
    : myLocation(theFrom), myAxis(theTo - theFrom) {
  myAxis.Normalize();
}

Line::Line(const Naive_Pnt3d &theLocation, const Naive_Vec3d &theDirection)
    : myLocation(theLocation), myAxis(theDirection) {
  myAxis.Normalize();
}

Line::Line(const Naive_Line_sf_t &theLineT)
    : myLocation(theLineT.basis_set.location), myAxis(theLineT.basis_set.axis) {
  myAxis.Normalize();
}

Naive_Vec3d Line::UnitTangent() const {
  Naive_Vec3d aDir = Direction();
  if (aDir.Normalize())
    return aDir;

  return Naive_Vec3d::Unset();
}

Naive_Real Line::FirstParameter() const { return -math::Constant::Infinite(); }

Naive_Real Line::LastParameter() const { return math::Constant::Infinite(); }

Naive_Bool Line::IsValid() const {
  return myLocation.IsValid() && myAxis.IsValid();
}

Handle_Naive_Geometry Line::Clone() const { return new Line(*this); }

Naive_Real Line::DistanceTo(const Naive_Pnt3d &thePnt) const {
  Naive_XYZ v = thePnt.XYZ() - myLocation.XYZ();
  Naive_Vec3d d = UnitTangent();
  if (!d.IsValid())
    return v.norm();

  Naive_Real t = v.dot(d.XYZ());
  Naive_XYZ p = myLocation.XYZ() - t * d.XYZ();
  return p.norm();
}

Naive_Pnt3d Line::PointAt(const Naive_Real theT) const {
  return {myLocation.XYZ() + myAxis.XYZ() * theT};
}

Naive_Vec3d Line::TangentAt(const Naive_Real theT) const { return Direction(); }

Naive_Code Line::Evaluate(const Naive_Real theT, const Naive_Integer theN,
                          Naive_Vec3dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  if (theN < 0)
    return Naive_Code_value_out_of_range;

  theD.resize(theN + 1, Naive_Vec3d::Zero());
  if (theN >= 0)
    theD[0].ChangeXYZ() = PointAt(theT).XYZ();
  if (theN >= 1)
    theD[1] = TangentAt(theT);

  return Naive_Code_ok;
}

Naive_Code Line::CurvatureAt(const Naive_Real theT, Naive_Vec3d &theV) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  theV = Naive_Vec3d::Zero();
  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry);
