#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Line);

Line::Line(const Naive_Ax1 &thePos) noexcept : myPos(thePos) {}

Line::Line(const Naive_Pnt3d &theLocation, const Naive_Vec3d &theDirection)
    : myPos(theLocation, theDirection) {}

Line::Line(const Naive_Line_sf_t &theLineSF) : myPos(theLineSF.basis_set) {}

Naive_Real Line::FirstParameter() const { return -math::Constant::Infinite(); }

Naive_Real Line::LastParameter() const { return math::Constant::Infinite(); }

Naive_Bool Line::IsValid() const { return myPos.IsValid(); }

Handle_Naive_Geometry Line::Clone() const { return new Line(*this); }

Naive_Real Line::DistanceTo(const Naive_Pnt3d &thePnt) const {
  Naive_XYZ v = thePnt.XYZ() - myPos.Location().XYZ();
  const Naive_Vec3d &d = myPos.Direction();
  if (!d.IsValid())
    return v.norm();

  Naive_Real t = v.dot(d.XYZ());
  Naive_XYZ p = myPos.Location().XYZ() - t * d.XYZ();
  return p.norm();
}

Naive_Pnt3d Line::PointAt(const Naive_Real theT) const {
  return {myPos.Location().XYZ() + myPos.Direction().XYZ() * theT};
}

Naive_Vec3d Line::TangentAt(const Naive_Real theT) const {
  return myPos.Direction();
}

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

Naive_Code Line::transform(const Naive_Trsf3d &theTrsf) {
  if (!myPos.Transform(theTrsf))
    return Naive_Code_err;
  return Naive_Code_ok;
}

Naive_Bool Line::IsClosed() const { return Naive_False; }

Naive_Bool Line::IsPeriodic() const { return Naive_False; }

Naive_Real Line::Period() const { return math::Constant::UnsetReal(); }

Naive_Code Line::Dump(Naive_Line_sf_t &theSF) const {
  return myPos.Dump(theSF.basis_set) ? Naive_Code_ok
                                     : Naive_Code_invalid_object;
}

Naive_NAMESPACE_END(geometry);
