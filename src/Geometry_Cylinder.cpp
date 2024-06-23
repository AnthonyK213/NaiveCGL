#include <naivecgl/Geometry/Cylinder.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_Bool Cylinder::IsValid() const { Naive_TODO; }

Handle_Naive_Geometry Cylinder::Clone() const { Naive_TODO; }

Naive_Pnt3d Cylinder::PointAt(const Naive_Real theU,
                              const Naive_Real theV) const {
  Naive_TODO;
}

Naive_Code Cylinder::Evaluate(const Naive_Real theU, const Naive_Real theV,
                              const Naive_Integer theN,
                              Naive_Vec3dList1 &theD) const {
  Naive_TODO;
}

Naive_NAMESPACE_END(geometry);
