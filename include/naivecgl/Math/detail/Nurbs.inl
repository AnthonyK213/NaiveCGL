#include "../Nurbs.h"

Naive_NAMESPACE_BEGIN(math);

template <typename OutTy_, Naive_Integer Dim_>
Naive_Code Nurbs::CurveEvaluate(const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
                                const Naive_RealList1 &theFlatKnots,
                                const Naive_RealList1 &theKnots,
                                const Naive_IntegerList1 &theMults,
                                const Naive_Integer theDegree,
                                const Naive_Real theT,
                                const Naive_Integer theDerN,
                                Naive_List1<OutTy_> &theResult) {
  if (theDerN < 0)
    return Naive_Code_value_out_of_range;

  // Naive_Integer iSpan = math::Nurbs::FindFlatSpan(theKnots, theMults, theT);
  // if (iSpan < 0)
  //   return Naive_Code_value_out_of_range;

  Naive_Integer aDerN = (::std::min)(theDerN, theDegree);
  Naive_RealList2 aDers = BasisFnDerEvalAll(
      theFlatKnots, theKnots, theMults, theCPs.size(), theDegree, theT, aDerN);
  Naive_List1<Naive_VNd<Dim_ + 1>> aCwDers(aDerN + 1,
                                           Naive_VNd<Dim_ + 1>::Zero());

  for (Naive_Integer d = 0; d <= aDerN; ++d) {
    for (Naive_Integer i = 0; i < aDers[d].size(); ++i) {
      aCwDers[d] += aDers[d][i] * theCPs[i];
    }
  }

  theResult.resize(aDerN + 1, OutTy_::Unset());

  for (Naive_Integer d = 0; d <= aDerN; ++d) {
    Naive_VNd<Dim_ + 1> v = aCwDers[d];
    for (Naive_Integer i = 1; i <= d; ++i) {
      v -= static_cast<Naive_Real>(math::Util::Combination(d, i)) *
           aCwDers[i](Dim_) * theResult[d - i].HomoCoord();
    }
    theResult[d] = OutTy_(v.template head<Dim_>() / aCwDers[0](Dim_));
  }

  return Naive_Code_ok;
}

template <Naive_Integer Dim_>
Naive_VNd<Dim_ + 1>
Nurbs::PoleAfterInsertKnot(const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
                           const Naive_RealList1 &theFlatKnots,
                           const Naive_Integer theDegree, const Naive_Real theT,
                           const Naive_Integer theK, const Naive_Integer theS,
                           const Naive_Integer theI, const Naive_Integer theM) {
  if (theM == 0)
    return theCPs[theI];

  if (theI <= theK - theDegree + theM - 1)
    return PoleAfterInsertKnot<Dim_>(theCPs, theFlatKnots, theDegree, theT,
                                     theK, theS, theI, theM - 1);

  if (theI >= theK - theS + 1)
    return PoleAfterInsertKnot<Dim_>(theCPs, theFlatKnots, theDegree, theT,
                                     theK, theS, theI - 1, theM - 1);

  auto q1 = PoleAfterInsertKnot<Dim_>(theCPs, theFlatKnots, theDegree, theT,
                                      theK, theS, theI, theM - 1);
  auto q2 = PoleAfterInsertKnot<Dim_>(theCPs, theFlatKnots, theDegree, theT,
                                      theK, theS, theI - 1, theM - 1);
  Naive_Real a =
      (theT - theFlatKnots[theI]) /
      (theFlatKnots[theI + theDegree - theM + 1] - theFlatKnots[theI]);

  return a * q1 + (1. - a) * q2;
}

template <Naive_Integer Dim_>
Naive_Code Nurbs::CurveRaiseDegree(
    const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
    const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
    const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
    const Naive_Integer theD, Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs,
    Naive_RealList1 &theNewKnots, Naive_IntegerList1 &theNewMults) {
  if (theD < 0)
    return Naive_Code_value_out_of_range;

  return Naive_Code_not_implemented;
}

template <Naive_Integer Dim_>
Naive_Code Nurbs::CurveIncreaseMultiplicity(
    const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
    const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
    const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
    const Naive_Real theI, const Naive_Integer theM,
    Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs, Naive_RealList1 &theNewKnots,
    Naive_IntegerList1 &theNewMults) {
  if (theI < 0 || theI >= theMults.size() || theM < 0)
    return Naive_Code_value_out_of_range;

  if (theM == 0)
    return Naive_Code_ok;

  Naive_Real T = theKnots[theI];
  Naive_Integer S = theMults[theI];

  if (theI != 0 && theI != theMults.size() - 1) {
    if (theM + S > theDegree)
      return Naive_Code_value_out_of_range;
  } else if (theM + S > theDegree + 1)
    return Naive_Code_value_out_of_range;

  /* The last knot belongs to the last span. */
  Naive_Integer iSpan = (theI == theMults.size() - 1) ? theI - 1 : theI;
  Naive_Integer K = ToFlatSpan(theMults, iSpan);

  theNewCPs.resize(theCPs.size() + theM);
  theNewKnots = theKnots;
  theNewMults = theMults;
  theNewMults[theI] += theM;

  for (Naive_Integer I = 0; I < theNewCPs.size(); ++I) {
    theNewCPs[I] = PoleAfterInsertKnot<Dim_>(theCPs, theFlatKnots, theDegree, T,
                                             K, S, I, theM);
  }

  return Naive_Code_ok;
}

template <Naive_Integer Dim_>
Naive_Code Nurbs::CurveInsertKnot(
    const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
    const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
    const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
    const Naive_Real theT, const Naive_Integer theM,
    Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs, Naive_RealList1 &theNewKnots,
    Naive_IntegerList1 &theNewMults) {
  if (theM < 0 || theM > theDegree)
    return Naive_Code_value_out_of_range;

  Naive_Integer iSpan = FindSpan(theKnots, theT);
  if (iSpan < 0)
    return Naive_Code_value_out_of_range;
  Naive_Integer K = ToFlatSpan(theMults, iSpan);

  if (theM == 0)
    return Naive_Code_ok;

  /* If |theT| is already in the |theKnots|, the operation would be a
   * multiplicity increase. */

  /* FIXME: Float equality? */

  if (theT == theKnots[iSpan])
    return CurveIncreaseMultiplicity<Dim_>(theCPs, theFlatKnots, theKnots,
                                           theMults, theDegree, iSpan, theM,
                                           theNewCPs, theNewKnots, theNewMults);

  if (theT == theKnots[iSpan + 1])
    return CurveIncreaseMultiplicity<Dim_>(theCPs, theFlatKnots, theKnots,
                                           theMults, theDegree, iSpan + 1, theM,
                                           theNewCPs, theNewKnots, theNewMults);

  /* Makes no sense for a inner knot with a multiplicity greater than
   * |theDegree|. */

  if (iSpan != 0 && iSpan != theMults.size() - 1) {
    if (theM > theDegree)
      return Naive_Code_value_out_of_range;
  } else if (theM > theDegree + 1)
    return Naive_Code_value_out_of_range;

  theNewCPs.resize(theCPs.size() + theM);
  theNewKnots = theKnots;
  theNewMults = theMults;
  theNewKnots.insert(theNewKnots.begin() + iSpan + 1, theT);
  theNewMults.insert(theNewMults.begin() + iSpan + 1, theM);

  for (Naive_Integer I = 0; I < theNewCPs.size(); ++I) {
    theNewCPs[I] = PoleAfterInsertKnot<Dim_>(theCPs, theFlatKnots, theDegree,
                                             theT, K, 0, I, theM);
  }

  return Naive_Code_ok;
}

template <Naive_Integer Dim_>
Naive_Code Nurbs::CurveRemoveKnot(
    const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
    const Naive_RealList1 &theFlatKnots, const Naive_RealList1 &theKnots,
    const Naive_IntegerList1 &theMults, const Naive_Integer theDegree,
    const Naive_Integer theI, const Naive_Integer theM,
    Naive_List1<Naive_VNd<Dim_ + 1>> &theNewCPs, Naive_RealList1 &theNewKnots,
    Naive_IntegerList1 &theNewMults) {
  if (theI < 0 || theI >= theMults.size())
    return Naive_Code_value_out_of_range;

  Naive_Integer S = theMults[theI];
  if (S == 0)
    return Naive_Code_index_out_of_range;

  Naive_Integer R = ToFlatSpan(theMults, theI);
  Naive_Integer N = S - theM;

  if (theM < 0 || N < 0)
    return Naive_Code_value_out_of_range;

  /* Nothing to do... */
  if (N == 0)
    return Naive_Code_ok;

  Naive_Integer aFirst = R - S;
  Naive_Integer aLast = R - theDegree;

  for (Naive_Integer t = 0; t < N; ++t) {
  }

  return Naive_Code_not_implemented;
}

Naive_NAMESPACE_END(math);
