#include <naivecgl/Geometry/ElementarySurface.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(ElementarySurface);

Naive_Code ElementarySurface::transform(const Naive_Trsf3d &theTrsf) {
  if (!myPos.Transform(theTrsf))
    return Naive_Code_err;
  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry);
