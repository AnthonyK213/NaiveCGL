#ifndef _NaiveCGL_Math_Nurbs_HeaderFile
#define _NaiveCGL_Math_Nurbs_HeaderFile

#include "Pnt3d.h"
#include "Polynomial.h"
#include "Util.h"
#include "Vec3d.h"

Naive_NAMESPACE_BEGIN(math);

class Nurbs {
public:
  Naive_EXPORT static Naive_Code
  CheckParam(const Naive_Integer nbCPs, const Naive_RealList1 &theKnots,
             const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
             Naive_Bool &myPeriodic, Naive_RealList1 &theFlatKnots);

  Naive_EXPORT static Naive_Integer FindSpan(const Naive_RealList1 &theKnots,
                                             const Naive_Real theT);

  Naive_EXPORT static Naive_Integer
  ToFlatSpan(const Naive_IntegerList1 &theMults, const Naive_Integer theSpan);

  Naive_EXPORT static Naive_Integer
  FindFlatSpan(const Naive_RealList1 &theKnots,
               const Naive_IntegerList1 &theMults, const Naive_Real theT);

  Naive_EXPORT static Polynomial BasisFn(const Naive_RealList1 &theFlatKnots,
                                         Naive_Integer theI, Naive_Integer theP,
                                         Naive_Integer theSpan);

  Naive_EXPORT static Naive_Real
  BasisFnEval(const Naive_RealList1 &theFlatKnots,
              const Naive_RealList1 &theKnots,
              const Naive_IntegerList1 &theMults, Naive_Integer theI,
              Naive_Integer theP, Naive_Real theT);

  Naive_EXPORT static Naive_RealList1
  BasisFnEvalAll(const Naive_RealList1 &theFlatKnots,
                 const Naive_RealList1 &theKnots,
                 const Naive_IntegerList1 &theMults, Naive_Integer theN,
                 Naive_Integer theD, Naive_Real theT);

  Naive_EXPORT static Naive_RealList2 BasisFnDerEvalAll(
      const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
      const Naive_IntegerList1 &theMults, Naive_Integer theNbCPs,
      Naive_Integer theDegree, Naive_Real theT, Naive_Integer theDer);

  template <typename OutTy_, Naive_Integer Dim_>
  static Naive_Code
  CurveEvaluate(const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
                const Naive_RealList1 &theFlatKnots,
                const Naive_RealList1 &theKnots,
                const Naive_IntegerList1 &theMults,
                const Naive_Integer theDegree, const Naive_Real theT,
                const Naive_Integer theDerN, Naive_List1<OutTy_> &theResult);

  template <Naive_Integer Dim_>
  static Naive_VNd<Dim_ + 1>
  PoleAfterInsertKnot(const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
                      const Naive_RealList1 &theFlatKnots,
                      const Naive_Integer theDegree, const Naive_Real theT,
                      const Naive_Integer theK, const Naive_Integer theS,
                      const Naive_Integer theI, const Naive_Integer theM);

  template <Naive_Integer Dim_>
  static Naive_Code CurveRaiseDegree(
      const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
      const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
      const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
      const Naive_Integer theD, Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs,
      Naive_RealList1 &theNewKnots, Naive_IntegerList1 &theNewMults);

  template <Naive_Integer Dim_>
  static Naive_Code CurveIncreaseMultiplicity(
      const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
      const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
      const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
      const Naive_Real theI, const Naive_Integer theM,
      Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs, Naive_RealList1 &theNewKnots,
      Naive_IntegerList1 &theNewMults);

  template <Naive_Integer Dim_>
  static Naive_Code CurveInsertKnot(
      const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
      const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
      const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
      const Naive_Real theT, const Naive_Integer theM,
      Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs, Naive_RealList1 &theNewKnots,
      Naive_IntegerList1 &theNewMults);

  template <Naive_Integer Dim_>
  static Naive_Code CurveRemoveKnot(
      const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
      const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
      const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
      const Naive_Integer theI, const Naive_Integer theM,
      Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs, Naive_RealList1 &theNewKnots,
      Naive_IntegerList1 &theNewMults);

  Naive_EXPORT static Naive_Code SurfaceEvaluate(
      const Naive_XYZWList2 &theCPs, const Naive_RealList1 &theUFlatKnots,
      const Naive_RealList1 &theVFlatKnots, const Naive_RealList1 &theUKnots,
      const Naive_RealList1 &theVKnots, const Naive_IntegerList1 &theUMults,
      const Naive_IntegerList1 &theVMults, const Naive_Integer theUDegree,
      const Naive_Integer theVDegree, const Naive_Real theU,
      const Naive_Real theV, const Naive_Integer theDerN,
      Naive_Vec3dList2 &theResult);
};

Naive_NAMESPACE_END(math);

#include "detail/Nurbs.inl"

#endif
