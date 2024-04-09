#ifndef _NaiveCGL_Math_Nurbs_HeaderFile
#define _NaiveCGL_Math_Nurbs_HeaderFile

#include "Constants.h"

Naive_NAMESPACE_BEGIN(math);

class Nurbs {
public:
  static Naive_Bool
  CheckParam(const Naive_Integer nbPoles, const Naive_RealList &theKnots,
             const Naive_IntegerList &theMults, const Naive_Integer theDegree,
             Naive_Bool &myPeriodic, Naive_RealList &theFlatKnots,
             Naive_IntegerList &theSpanIdx);
};

Naive_NAMESPACE_END(math);

#endif
