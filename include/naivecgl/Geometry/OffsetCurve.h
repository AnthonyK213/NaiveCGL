#ifndef _NaiveCGL_Geometry_OffsetCurve_HeaderFile
#define _NaiveCGL_Geometry_OffsetCurve_HeaderFile

#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry);

class OffsetCurve : public Naive_Curve {
public:
  Naive_DEFINE_RTTI(OffsetCurve, Naive_Curve);

protected:
  Naive_EXPORT virtual Naive_Code
  transform(const math::Trsf3d &theTrsf) Naive_OVERRIDE;

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_OffsetCurve = ::naivecgl::geometry::OffsetCurve;
Naive_DEFINE_HANDLE(Naive_OffsetCurve);

#endif
