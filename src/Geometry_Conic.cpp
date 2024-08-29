#include <naivecgl/Geometry/Conic.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Conic);

Naive_Code Conic::transform(const math::Trsf3d &theTrsf) {
  if (!myPos.Transform(theTrsf))
    return Naive_Code_err;
  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry);
