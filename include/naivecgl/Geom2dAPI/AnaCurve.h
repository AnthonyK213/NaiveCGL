#ifndef _NaiveCGL_Geom2dAPI_AnaCurve_HeaderFile
#define _NaiveCGL_Geom2dAPI_AnaCurve_HeaderFile

#include "../Geometry2d/Curve.h"
#include "../Math/Precision.h"

Naive_NAMESPACE_BEGIN(geom2d_api);

class AnaCurve {
public:
  Naive_EXPORT static Naive_Bool
  IsLinear(const Handle_Naive_Curve2d &theCrv2d,
           const Naive_Real theTol = math::Precision::Epsilon0());

  Naive_EXPORT static Naive_Bool
  IsArc(const Handle_Naive_Curve2d &theCrv2d,
        const Naive_Real theTol = math::Precision::Epsilon0());

  Naive_EXPORT static Naive_Bool
  IsPlanar(const Handle_Naive_Curve2d &theCrv2d,
           const Naive_Real theTol = math::Precision::Epsilon0());

  Naive_EXPORT static Naive_Code
  GetProps(const Handle_Naive_Curve2d &theCrv2d,
           const Naive_Real theTol = math::Precision::Epsilon0());
};

Naive_NAMESPACE_END(geom2d_api);

#endif
