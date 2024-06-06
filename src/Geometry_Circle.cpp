#include <naivecgl/Geometry/Circle.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Circle::Circle() {}

Circle::Circle(const Plane &thePlane, const Naive_Real theRadius)
    : myPlane(thePlane), myRadius(theRadius) {}

Naive_Bool Circle::IsValid() const {
  return myPlane.IsValid() && math::Util::IsValidReal(myRadius) && myRadius > 0;
}

Handle_Naive_Geometry Circle::Clone() const { return new Circle(*this); }

Naive_Real Circle::FirstParameter() const { return 0.0; }

Naive_Real Circle::LastParameter() const { return math::Constant::TwoPI(); }

Naive_Point3d Circle::PointAt(const Naive_Real theT) const {
  return {myPlane.Location().XYZ() +
          myPlane.XAxis().XYZ() * myRadius * ::std::cos(theT) +
          myPlane.YAxis().XYZ() * myRadius * ::std::sin(theT)};
}

Naive_Vector3d Circle::TangentAt(const Naive_Real theT) const {
  return {(-myPlane.XAxis().XYZ() * ::std::sin(theT) +
           myPlane.YAxis().XYZ() * ::std::cos(theT)) *
          myRadius};
}

Naive_Bool Circle::DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
                                Naive_Vector3dList &theD) const {
  if (!IsValid() || theN < 0)
    return false;

  Naive_Real s = ::std::sin(theT) * myRadius;
  Naive_Real c = ::std::cos(theT) * myRadius;
  auto f = [&](const Naive_Real a, const Naive_Real b) {
    return myPlane.XAxis().XYZ() * a + myPlane.YAxis().XYZ() * b;
  };

  theD.resize(theN + 1, Vector3d::Unset());

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

  return true;
}

Naive_Vector3d Circle::CurvatureAt(const Naive_Real theT) const {
  if (!IsValid())
    return Naive_Vector3d::Unset();

  Naive_Vector3dList aD{};
  if (!DerivativeAt(theT, 2, aD))
    return Naive_Vector3d::Unset();

  return aD[2].Divided(myRadius * myRadius);
}

Naive_NAMESPACE_END(geometry);
