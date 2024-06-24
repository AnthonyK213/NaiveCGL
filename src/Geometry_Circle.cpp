#include <naivecgl/Geometry/Circle.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Circle::Circle() {}

Circle::Circle(const Naive_Ax2 &theAx2, const Naive_Real theR)
    : myRadius(theR) {
  myPos = theAx2;
}

Naive_Bool Circle::IsValid() const {
  return myPos.IsValid() && math::Util::IsValidReal(myRadius) && myRadius > 0;
}

Handle_Naive_Geometry Circle::Clone() const { return new Circle(*this); }

Naive_Real Circle::FirstParameter() const { return 0.0; }

Naive_Real Circle::LastParameter() const { return math::Constant::TwoPI(); }

Naive_Pnt3d Circle::PointAt(const Naive_Real theT) const {
  return {myPos.Location().XYZ() +
          myPos.XDirection().XYZ() * myRadius * ::std::cos(theT) +
          myPos.YDirection().XYZ() * myRadius * ::std::sin(theT)};
}

Naive_Vec3d Circle::TangentAt(const Naive_Real theT) const {
  return {(-myPos.XDirection().XYZ() * ::std::sin(theT) +
           myPos.YDirection().XYZ() * ::std::cos(theT)) *
          myRadius};
}

Naive_Code Circle::DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
                                Naive_Vec3dList1 &theD) const {

  if (!IsValid())
    return Naive_Code_invalid_handle;

  if (theN < 0)
    return Naive_Code_value_out_of_range;

  Naive_Real s = ::std::sin(theT) * myRadius;
  Naive_Real c = ::std::cos(theT) * myRadius;
  auto f = [&](const Naive_Real a, const Naive_Real b) {
    return myPos.XDirection().XYZ() * a + myPos.YDirection().XYZ() * b;
  };

  theD.resize(theN + 1, Naive_Vec3d::Unset());

  if (theN >= 0)
    theD[0].ChangeXYZ() = PointAt(theT).XYZ();

  for (Naive_Integer i = 1; i <= theN; ++i) {
    switch (theN % 4) {
    case 0:
      theD[i].ChangeXYZ() = f(c, s);
      break;

    case 1:
      theD[i].ChangeXYZ() = f(-s, c);
      break;

    case 2:
      theD[i].ChangeXYZ() = -f(c, s);
      break;

    case 3:
      theD[i].ChangeXYZ() = f(s, -c);
      break;

    default:
      break;
    }
  }

  return Naive_Code_ok;
}

Naive_Code Circle::CurvatureAt(const Naive_Real theT, Naive_Vec3d &theV) const {
  if (!IsValid())
    return Naive_Code_invalid_handle;

  Naive_Vec3dList1 aD{};
  Naive_Code aCode = DerivativeAt(theT, 2, aD);
  if (aCode)
    return aCode;

  theV = aD[2].Divided(myRadius * myRadius);
  return aCode;
}

Naive_NAMESPACE_END(geometry);
