#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(geometry);

Line::Line(const Naive_Point3d &theFrom, const Naive_Point3d &theTo)
    : myLocation(theFrom), myAxis(theTo - theFrom) {
  myAxis.Normalize();
}

Line::Line(const Naive_Point3d &theLocation, const Naive_Vector3d &theDirection)
    : myLocation(theLocation), myAxis(theDirection) {
  myAxis.Normalize();
}

Line::Line(const Naive_Line_t &theLineT)
    : myLocation(theLineT.basis_set.location), myAxis(theLineT.basis_set.axis) {
  myAxis.Normalize();
}

Naive_Vector3d Line::UnitTangent() const {
  Naive_Vector3d aDir = Direction();
  if (aDir.Normalize())
    return aDir;

  return Naive_Vector3d::Unset();
}

Naive_Real Line::FirstParameter() const { return -math::Constant::MaxReal(); }

Naive_Real Line::LastParameter() const { return math::Constant::MaxReal(); }

Naive_Bool Line::IsValid() const {
  return myLocation.IsValid() && myAxis.IsValid();
}

Handle_Naive_Geometry Line::Clone() const { return new Line(*this); }

Naive_Real Line::DistanceTo(const Naive_Point3d &thePnt) const {
  Naive_XYZ v = thePnt.XYZ() - myLocation.XYZ();
  Naive_Vector3d d = UnitTangent();
  if (!d.IsValid())
    return v.norm();

  Naive_Real t = v.dot(d.XYZ());
  Naive_XYZ p = myLocation.XYZ() - t * d.XYZ();
  return p.norm();
}

Naive_Point3d Line::PointAt(const Naive_Real theT) const {
  return {myLocation.XYZ() + myAxis.XYZ() * theT};
}

Naive_Vector3d Line::TangentAt(const Naive_Real theT) const {
  return Direction();
}

Naive_Bool Line::DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
                              Naive_Vector3dList &theD) const {
  if (!IsValid() || theN < 0)
    return Naive_False;

  theD.resize(theN + 1, Naive_Vector3d::Zero());
  if (theN >= 0)
    theD[0].ChangeXYZ() = PointAt(theT).XYZ();
  if (theN >= 1)
    theD[1] = TangentAt(theT);

  return Naive_True;
}

Naive_Vector3d Line::CurvatureAt(const Naive_Real theT) const {
  return Naive_Vector3d::Zero();
}

Naive_NAMESPACE_END(geometry);
