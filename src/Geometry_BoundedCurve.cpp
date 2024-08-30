#include <naivecgl/Geometry/BoundedCurve.h>
#include <naivecgl/Math/Precision.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(BoundedCurve);

Naive_Bool BoundedCurve::IsClosed() const {
  return StartPoint().DistanceToSquared(EndPoint()) <=
         math::Precision::SquareEpsilon0();
}

Naive_NAMESPACE_END(geometry);
