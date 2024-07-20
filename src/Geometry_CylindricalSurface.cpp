#include <naivecgl/Geometry/CylindricalSurface.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(CylindricalSurface);

Naive_Bool CylindricalSurface::IsValid() const { Naive_TODO; }

Handle_Naive_Geometry CylindricalSurface::Clone() const { Naive_TODO; }

Naive_Pnt3d CylindricalSurface::PointAt(const Naive_Real theU,
                                        const Naive_Real theV) const {
  Naive_TODO;
}

Naive_Code CylindricalSurface::Evaluate(const Naive_Real theU,
                                        const Naive_Real theV,
                                        const Naive_Integer theN,
                                        Naive_Vec3dList1 &theD) const {
  Naive_TODO;
}

Naive_NAMESPACE_END(geometry);
