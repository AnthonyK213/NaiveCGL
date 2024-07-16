#ifndef _NaiveCGL_GeomAPI_AnaCurve_HeaderFile
#define _NaiveCGL_GeomAPI_AnaCurve_HeaderFile

#include "../Geometry/Curve.h"

Naive_NAMESPACE_BEGIN(geomapi);

class AnaCurve {
public:
  Naive_EXPORT static Naive_Bool
  IsLinear(const Handle_Naive_Curve &theCrv,
           const Naive_Real theTol = math::Precision::Epsilon0());

  Naive_EXPORT static Naive_Bool
  IsArc(const Handle_Naive_Curve &theCrv,
        const Naive_Real theTol = math::Precision::Epsilon0());

  Naive_EXPORT static Naive_Bool
  IsPlanar(const Handle_Naive_Curve &theCrv,
           const Naive_Real theTol = math::Precision::Epsilon0());

  Naive_EXPORT static Naive_Code
  GetProps(const Handle_Naive_Curve &theCrv,
           const Naive_Real theTol = math::Precision::Epsilon0());
};

Naive_NAMESPACE_END(geomapi);

#endif
