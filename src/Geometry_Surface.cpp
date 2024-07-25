#include <naivecgl/Geometry/Surface.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Surface);

Naive_Pnt3d Surface::PointAt(const Naive_Real theU,
                             const Naive_Real theV) const {
  Naive_Vec3dList1 aD{};
  if (Evaluate(theU, theV, 0, aD) != Naive_Code_ok)
    return Naive_Pnt3d::Unset();
  return aD[0].XYZ();
}

Naive_NAMESPACE_END(geometry);
