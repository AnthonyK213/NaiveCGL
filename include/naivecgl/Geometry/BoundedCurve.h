#ifndef _NaiveCGL_Geometry_BoundedCurve_HeaderFile
#define _NaiveCGL_Geometry_BoundedCurve_HeaderFile

#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry);

class BoundedCurve : public Naive_Curve {
public:
  Naive_EXPORT virtual Naive_Pnt3d EndPoint() const = 0;

  Naive_EXPORT virtual Naive_Pnt3d StartPoint() const = 0;

  Naive_DEFINE_RTTI(BoundedCurve, Naive_Curve);
};

Naive_NAMESPACE_END(geometry);

using Naive_BoundedCurve = ::naivecgl::geometry::BoundedCurve;
Naive_DEFINE_HANDLE(Naive_BoundedCurve);

#endif
