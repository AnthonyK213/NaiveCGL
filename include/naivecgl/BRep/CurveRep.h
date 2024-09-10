#ifndef _NaiveCGL_BRep_CurveRep_HeaderFile
#define _NaiveCGL_BRep_CurveRep_HeaderFile

#include "../Geometry/Curve.h"

Naive_NAMESPACE_BEGIN(brep);

class CurveRep : public Naive_Curve {
public:
  Naive_EXPORT virtual Handle_Naive_Curve ComputeCurve3d() const = 0;

  Naive_DEFINE_RTTI(CurveRep, Naive_Curve);

protected:
};

Naive_NAMESPACE_END(brep);

#endif
