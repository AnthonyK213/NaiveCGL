#include <naivecgl/Geometry2d/Curve.h>

Naive_NAMESPACE_BEGIN(geometry2d);

Naive_IMPLEMENT_RTTI(Curve);

Naive_Pnt2d Curve::PointAt(const Naive_Real theT) const {
  Naive_Vec2dList1 aD{};
  if (Evaluate(theT, 0, aD) != Naive_Code_ok)
    return Naive_Pnt2d::Unset();
  return aD[0].XY();
}

Naive_Vec2d Curve::TangentAt(const Naive_Real theT) const {
  Naive_Vec2dList1 aD{};
  if (Evaluate(theT, 1, aD) != Naive_Code_ok)
    return Naive_Vec2d::Unset();
  return aD[1];
}

Naive_NAMESPACE_END(geometry2d);
