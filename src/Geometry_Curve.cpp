#include <naivecgl/Geometry/Curve.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Curve);

Naive_Pnt3d Curve::PointAt(const Naive_Real theT) const {
  Naive_Vec3dList1 aD{};
  if (Evaluate(theT, 0, aD) != Naive_Code_ok)
    return Naive_Pnt3d::Unset();
  return aD[0].XYZ();
}

Naive_Vec3d Curve::TangentAt(const Naive_Real theT) const {
  Naive_Vec3dList1 aD{};
  if (Evaluate(theT, 1, aD) != Naive_Code_ok)
    return Naive_Vec3d::Unset();
  return aD[1];
}

Naive_NAMESPACE_END(geometry);
