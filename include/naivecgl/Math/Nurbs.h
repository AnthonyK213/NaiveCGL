#ifndef _NaiveCGL_Math_Nurbs_HeaderFile
#define _NaiveCGL_Math_Nurbs_HeaderFile

#include "Constant.h"
#include "Polynomial.h"

Naive_NAMESPACE_BEGIN(math);

class Nurbs {
public:
  Naive_EXPORT static Naive_Bool
  CheckParam(const Naive_Integer nbPoles, const Naive_RealList &theKnots,
             const Naive_IntegerList &theMults, const Naive_Integer theDegree,
             Naive_Bool &myPeriodic, Naive_RealList &theFlatKnots,
             Naive_IntegerList &theSpanIdx);

  Naive_EXPORT static Naive_Integer FindSpan(const Naive_RealList &theKnots,
                                             const Naive_Real theT);

  Naive_EXPORT static Naive_Integer
  FindFlatSpan(const Naive_RealList &theKnots,
               const Naive_IntegerList &theSpanIdx, const Naive_Real theT);

  Naive_EXPORT static Polynomial BasisFn(const Naive_RealList &theFlatKnots,
                                         Naive_Integer theI, Naive_Integer theP,
                                         Naive_Integer theSpan);
};

Naive_NAMESPACE_END(math);

#endif
