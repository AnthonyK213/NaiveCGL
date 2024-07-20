#ifndef _NaiveCGL_Geometry2d_TrimmedCurve_HeaderFile
#define _NaiveCGL_Geometry2d_TrimmedCurve_HeaderFile

#include "BoundedCurve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class TrimmedCurve : public Naive_BoundedCurve2d {
public:
  Naive_DEFINE_RTTI(TrimmedCurve, Naive_BoundedCurve2d);

private:
  Handle_Naive_Curve2d myBasisCurve;
  Naive_Real myT1;
  Naive_Real myT2;
};

Naive_NAMESPACE_END(geometry2d);

using Naive_TrimmedCurve2d = ::naivecgl::geometry2d::TrimmedCurve;
Naive_DEFINE_HANDLE(Naive_TrimmedCurve2d);

#endif
