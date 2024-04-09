#ifndef _NaiveCGL_Math_Nurbs_HeaderFile
#define _NaiveCGL_Math_Nurbs_HeaderFile

#include "Constant.h"

Naive_NAMESPACE_BEGIN(math);

class Nurbs {
public:
  static Naive_Bool
  CheckParam(const Naive_Integer nbPoles, const Naive_RealList &theKnots,
             const Naive_IntegerList &theMults, const Naive_Integer theDegree,
             Naive_Bool &myPeriodic, Naive_RealList &theFlatKnots,
             Naive_IntegerList &theSpanIdx);

  static Naive_Integer FindSpan(const Naive_RealList &theKnots,
                                const Naive_IntegerList &theSpanIdx,
                                const Naive_Real theT);

  static Naive_Real BasisFn(const Naive_RealList &theFlatKnots,
                            Naive_Integer theI, Naive_Integer theP,
                            Naive_Real theT, Naive_Integer theSpan);
};

Naive_NAMESPACE_END(math);

#endif
