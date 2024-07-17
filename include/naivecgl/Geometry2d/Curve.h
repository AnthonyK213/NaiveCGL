#ifndef _NaiveCGL_Geometry2d_Curve_HeaderFile
#define _NaiveCGL_Geometry2d_Curve_HeaderFile

#include "../Math/Pnt2d.h"
#include "../Math/Vec2d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Curve : public Naive_Geometry2d {
public:
  Naive_EXPORT virtual Naive_Real FirstParameter() const = 0;

  Naive_EXPORT virtual Naive_Real LastParameter() const = 0;

  Naive_EXPORT virtual Naive_Pnt2d PointAt(const Naive_Real theT) const = 0;

  Naive_EXPORT virtual Naive_Vec2d TangentAt(const Naive_Real theT) const = 0;

  Naive_EXPORT virtual Naive_Code Evaluate(const Naive_Real theT,
                                           const Naive_Integer theN,
                                           Naive_Vec2dList1 &theD) const = 0;

  Naive_EXPORT virtual Naive_Code CurvatureAt(const Naive_Real theT,
                                              Naive_Vec2d &theV) const = 0;

  Naive_DEFINE_RTTI(Curve, Naive_Geometry2d);
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Curve2d = ::naivecgl::geometry2d::Curve;
Naive_DEFINE_HANDLE(Naive_Curve2d);

#endif
