#ifndef _NaiveCGL_Geometry_TrimmedCurve_HeaderFile
#define _NaiveCGL_Geometry_TrimmedCurve_HeaderFile

#include "BoundedCurve.h"

Naive_NAMESPACE_BEGIN(geometry);

class TrimmedCurve : public Naive_BoundedCurve {
public:
  Naive_DEFINE_RTTI(TrimmedCurve, Naive_BoundedCurve);

private:
  Handle_Naive_Curve myBasisCurve;
  Naive_Real myT1;
  Naive_Real myT2;
};

Naive_NAMESPACE_END(geometry);

using Naive_TrimmedCurve = ::naivecgl::geometry::TrimmedCurve;
Naive_DEFINE_HANDLE(Naive_TrimmedCurve);

#endif
