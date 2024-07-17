#ifndef _NaiveCGL_Geometry2d_BoundedCurve_HeaderFile
#define _NaiveCGL_Geometry2d_BoundedCurve_HeaderFile

#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class BoundedCurve : public Naive_Curve2d {
public:
  Naive_EXPORT virtual Naive_Pnt2d EndPoint() const = 0;

  Naive_EXPORT virtual Naive_Pnt2d StartPoint() const = 0;

  Naive_DEFINE_RTTI(BoundedCurve, Naive_Curve2d);
};

Naive_NAMESPACE_END(geometry2d);

using Naive_BoundedCurve2d = ::naivecgl::geometry2d::BoundedCurve;
Naive_DEFINE_HANDLE(Naive_BoundedCurve2d);

#endif
