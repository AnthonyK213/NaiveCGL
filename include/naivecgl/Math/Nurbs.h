#ifndef _NaiveCGL_Math_Nurbs_HeaderFile
#define _NaiveCGL_Math_Nurbs_HeaderFile

#include "Pnt3d.h"

Naive_NAMESPACE_BEGIN(math);

class Polynomial;

class Nurbs {
public:
  Naive_EXPORT static Naive_Code
  CheckParam(const Naive_Integer nbPoles, const Naive_Integer nbWeights,
             const Naive_RealList1 &theKnots,
             const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
             Naive_Bool &myPeriodic, Naive_RealList1 &theFlatKnots,
             Naive_IntegerList1 &theSpanIdx);

  Naive_EXPORT static Naive_Integer FindSpan(const Naive_RealList1 &theKnots,
                                             const Naive_Real theT);

  Naive_EXPORT static Naive_Integer
  FindFlatSpan(const Naive_RealList1 &theKnots,
               const Naive_IntegerList1 &theSpanIdx, const Naive_Real theT);

  Naive_EXPORT static Polynomial BasisFn(const Naive_RealList1 &theFlatKnots,
                                         Naive_Integer theI, Naive_Integer theP,
                                         Naive_Integer theSpan);

  Naive_EXPORT static Naive_XYZW PoleAfterInsertKnot(
      const Naive_Pnt3dList1 &thePoles, const Naive_RealList1 &theWeights,
      const Naive_RealList1 &theFlatKnots, const Naive_Integer theDegree,
      const Naive_Real theT, const Naive_Integer theK, const Naive_Integer theS,
      const Naive_Integer theI, const Naive_Integer theM);
};

Naive_NAMESPACE_END(math);

#endif
