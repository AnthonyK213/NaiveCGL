#include <naivecgl/Geometry2d/Line.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(geometry2d);

Naive_IMPLEMENT_RTTI(Line);

Line::Line(const Naive_Ax2d &thePos) noexcept : myPos(thePos) {}

Line::Line(const Naive_Pnt2d &theLocation, const Naive_Vec2d &theDirection)
    : myPos(theLocation, theDirection) {}

Line::Line(const Naive_Line2d_sf_t &theLine2dSF)
    : myPos(theLine2dSF.basis_set) {}

Naive_Real Line::FirstParameter() const { return -math::Constant::Infinite(); }

Naive_Real Line::LastParameter() const { return math::Constant::Infinite(); }

Naive_Bool Line::IsValid() const { return myPos.IsValid(); }

Handle_Naive_Geometry2d Line::Clone() const { return new Line(*this); }

Naive_Real Line::DistanceTo(const Naive_Pnt2d &thePnt) const {
  Naive_XY v = thePnt.XY() - myPos.Location().XY();
  const Naive_Vec2d &d = myPos.Direction();
  if (!d.IsValid())
    return v.norm();

  Naive_Real t = v.dot(d.XY());
  Naive_XY p = myPos.Location().XY() - t * d.XY();
  return p.norm();
}

Naive_Pnt2d Line::PointAt(const Naive_Real theT) const {
  return {myPos.Location().XY() + myPos.Direction().XY() * theT};
}

Naive_Vec2d Line::TangentAt(const Naive_Real theT) const {
  return myPos.Direction();
}

Naive_Code Line::Evaluate(const Naive_Real theT, const Naive_Integer theN,
                          Naive_Vec2dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  if (theN < 0)
    return Naive_Code_value_out_of_range;

  theD.resize(theN + 1, Naive_Vec2d::Zero());
  if (theN >= 0)
    theD[0].ChangeXY() = PointAt(theT).XY();
  if (theN >= 1)
    theD[1] = TangentAt(theT);

  return Naive_Code_ok;
}

Naive_Code Line::CurvatureAt(const Naive_Real theT, Naive_Vec2d &theV) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  theV = Naive_Vec2d::Zero();
  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry2d);
