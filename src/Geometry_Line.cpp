#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(geometry);

Line::Line(const Naive_Point3d &theFrom, const Naive_Point3d &theTo)
    : myFrom(theFrom), myTo(theTo) {}

Line::Line(const Naive_Point3d &theStart, const Naive_Vector3d &theDirection,
           const Naive_Real theLength) {}

Line::Line(const Naive_Point3d &theStart, const Naive_Vector3d &theSpan) {}

Line::Line(const Naive_Line_t &theLineT)
    : myFrom(theLineT.from), myTo(theLineT.to) {}

Naive_Vector3d Line::UnitTangent() const {
  Naive_Vector3d aDir = Direction();
  if (aDir.Normalize())
    return aDir;

  return Naive_Vector3d::Unset();
}

Naive_Real Line::FirstParameter() const { return 0.0; }

Naive_Real Line::LastParameter() const { return 1.0; }

Naive_Bool Line::IsValid() const {
  return myFrom.IsValid() && myFrom.IsValid() &&
         Length() > math::Constant::ZeroTolerance();
}

Handle_Naive_Geometry Line::Clone() const { return new Line(*this); }

Naive_Real Line::DistanceTo(const Naive_Point3d &thePnt,
                            const Naive_Bool theFinite) const {
  Naive_XYZ v = thePnt.XYZ() - myFrom.XYZ();
  Naive_Vector3d d = UnitTangent();
  if (!d.IsValid()) {
    return v.norm();
  }

  Naive_Real t = v.dot(d.XYZ());

  if (theFinite && (t < 0. || t > Length())) {
    Naive_Real d1 = v.norm();
    Naive_Real d2 = (thePnt.XYZ() - myTo.XYZ()).norm();
    return (::std::min)(d1, d2);
  } else {
    Naive_XYZ p = myFrom.XYZ() - t * d.XYZ();
    return p.norm();
  }
}

Naive_Point3d Line::PointAt(const Naive_Real theT) const {
  return {myFrom.XYZ() * (1 - theT) + myTo.XYZ() * theT};
}

Naive_Vector3d Line::TangentAt(const Naive_Real theT) const {
  return Direction();
}

Naive_Bool Line::DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
                              Naive_Vector3dList &theD) const {
  if (!IsValid() || theN < 0)
    return false;

  theD.resize(theN + 1, Naive_Vector3d::Zero());
  if (theN >= 0)
    theD[0].ChangeXYZ() = PointAt(theT).XYZ();
  if (theN >= 1)
    theD[1] = TangentAt(theT);

  return true;
}

Naive_Vector3d Line::CurvatureAt(const Naive_Real theT) const {
  return Naive_Vector3d::Zero();
}

Naive_Point3d Line::PointAtLength(const Naive_Real theLength) const {
  Naive_Vector3d aTan = UnitTangent();
  if (!aTan.IsValid())
    return Naive_Point3d::Unset();

  return {myFrom.XYZ() + aTan.XYZ() * theLength};
}

Naive_NAMESPACE_END(geometry);
