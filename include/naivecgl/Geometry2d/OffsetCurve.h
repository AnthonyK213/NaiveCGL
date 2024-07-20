#ifndef _NaiveCGL_Geometry2d_OffsetCurve_HeaderFile
#define _NaiveCGL_Geometry2d_OffsetCurve_HeaderFile

#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class OffsetCurve : public Naive_Curve2d {
public:
  Naive_DEFINE_RTTI(OffsetCurve, Naive_Curve2d);

protected:
private:
};

Naive_NAMESPACE_END(geometry2d);

using Naive_OffsetCurve2d = ::naivecgl::geometry2d::OffsetCurve;
Naive_DEFINE_HANDLE(Naive_OffsetCurve2d);

#endif
