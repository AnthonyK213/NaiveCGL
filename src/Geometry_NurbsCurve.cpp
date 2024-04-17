#include <naivecgl/Geometry/NurbsCurve.h>

Naive_NAMESPACE_BEGIN(geometry);

NurbsCurve::NurbsCurve(const Naive_Point3dList &thePoles,
                       const Naive_RealList &theWeights,
                       const Naive_RealList &theKnots,
                       const Naive_IntegerList &theMults,
                       const Naive_Integer theDegree)
    : myDegree(0), myRational(false), myPeriodic(false), myFlatKnots(),
      mySpanIdx() {
  update(thePoles, theWeights, theKnots, theMults, theDegree);
}

Naive_Integer NurbsCurve::NbPoles() const {
  if (!isValid())
    return 0;
  return static_cast<Naive_Integer>(myPoles.size());
}

const Naive_Point3d &NurbsCurve::Pole(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbPoles() || !isValid())
    return Naive_Point3d::Unset();
  return myPoles[theIndex];
}

Naive_EXPORT Naive_Real NurbsCurve::Weight(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbPoles() || !isValid())
    return math::Constant::UnsetReal();
  return myWeights[theIndex];
}

Naive_Integer NurbsCurve::NbKnots() const {
  if (!isValid())
    return 0;
  return static_cast<Naive_Integer>(myKnots.size());
}

Naive_Real NurbsCurve::Knot(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbKnots() || !isValid())
    return math::Constant::UnsetReal();
  return myKnots[theIndex];
}

Naive_Integer NurbsCurve::Multiplicity(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbKnots() || !isValid())
    return math::Constant::UnsetReal();
  return myMults[theIndex];
}

Naive_Real NurbsCurve::FirstParameter() const {
  if (!isValid())
    return math::Constant::UnsetReal();
  return myKnots[0];
}

Naive_Real NurbsCurve::LastParameter() const {
  if (!isValid())
    return math::Constant::UnsetReal();
  return myKnots[myKnots.size() - 1];
}

Naive_Point3d NurbsCurve::PointAt(const Naive_Real theT) const {
  Naive_Vector3dList aD{};
  if (!DerivativeAt(theT, 0, aD))
    return Naive_Point3d::Unset();
  return aD[0].XYZ();
}

Naive_Vector3d NurbsCurve::TangentAt(const Naive_Real theT) const {
  Naive_Vector3dList aD{};
  if (!DerivativeAt(theT, 1, aD))
    return Naive_Vector3d::Unset();
  return aD[1];
}

Naive_Bool NurbsCurve::DerivativeAt(const Naive_Real theT,
                                    const Naive_Integer theN,
                                    Naive_Vector3dList &theD) const {
  if (!isValid())
    return false;

  if (theN < 0)
    return false;

  Naive_Integer iSpan = math::Nurbs::FindFlatSpan(myKnots, mySpanIdx, theT);
  if (iSpan < 0)
    return false;

  Naive_RealList aWBuf(theN + 1, math::Constant::UnsetReal());
  theD.resize(theN + 1, Naive_Vector3d::Unset());
  Naive_List<math::Polynomial> anA{};
  anA.reserve(Degree() + 1);
  Naive_Integer pBegin = (::std::max)(0, iSpan - Degree());
  Naive_Integer pEnd = iSpan;
  for (Naive_Integer i = pBegin; i <= pEnd; ++i) {
    auto b = math::Nurbs::BasisFn(myFlatKnots, i, Degree(), iSpan);
    anA.emplace_back(::std::move(b));
  }

  for (Naive_Integer I = 0; I <= theN; ++I) {
    Naive_XYZ A{0., 0., 0.};
    Naive_Real W = 0.0;
    for (Naive_Integer k = pBegin; k <= pEnd; ++k) {
      Naive_Real N =
          anA[k - pBegin].Derivative(I).Evaluate(theT) * myWeights[k];
      A += N * myPoles[k].XYZ();
      W += N;
    }

    aWBuf[I] = W;

    for (Naive_Integer k = 1; k <= I; ++k) {
      A -= static_cast<Naive_Real>(math::Util::Combination(I, k)) * aWBuf[k] *
           theD[I - k].XYZ();
    }

    theD[I].ChangeXYZ() = A / aWBuf[0];
  }

  return true;
}

Naive_Bool NurbsCurve::IncreaseMultiplicity(const Naive_Integer theI,
                                            const Naive_Integer theM) {
  if (theI < 0 || theI >= myMults.size() || theM < 0)
    return false;

  if (theM == 0)
    return true;

  if (theI != 0 && theI != myMults.size() - 1) {
    if (theM + myMults[theI] > myDegree)
      return false;
  } else if (theM + myMults[theI] > myDegree + 1)
    return false;

  // TODO: Implementation.

  return true;
}

Naive_Bool NurbsCurve::InsertKnot(const Naive_Real theT,
                                  const Naive_Integer theM) {
  if (theM <= 0 || theM > Degree())
    return false;

  Naive_Integer iSpan = math::Nurbs::FindSpan(myKnots, theT);
  if (iSpan < 0)
    return false;
  Naive_Integer K = mySpanIdx[iSpan] - 1;

  // FIXME: Float equality?

  if (theT == myKnots[iSpan])
    return IncreaseMultiplicity(iSpan, theM);

  if (theT == myKnots[iSpan + 1])
    return IncreaseMultiplicity(iSpan + 1, theM);

  // TODO: Insert knot with multiplicity |theM|?

  Naive_Point3dList aPoles(myPoles.size() + 1, Naive_Point3d::Unset());
  Naive_RealList aWeights(myWeights.size() + 1, math::Constant::UnsetReal());
  Naive_RealList aKnots = myKnots;
  Naive_IntegerList aMults = myMults;
  aKnots.insert(aKnots.begin() + iSpan + 1, theT);
  aMults.insert(aMults.begin() + iSpan + 1, theM);
  for (Naive_Integer i = 0; i <= myPoles.size(); ++i) {
    if (i <= K - Degree()) {
      aPoles[i].ChangeXYZ() = myPoles[i].XYZ();
      aWeights[i] = myWeights[i];
    } else if (i >= K + 1) {
      aPoles[i].ChangeXYZ() = myPoles[i - 1].XYZ();
      aWeights[i] = myWeights[i - 1];
    } else {
      Naive_Real a = (theT - myFlatKnots[i]) /
                     (myFlatKnots[i + Degree()] - myFlatKnots[i]);
      aPoles[i].ChangeXYZ() =
          a * myPoles[i].XYZ() + (1. - a) * myPoles[i - 1].XYZ();
      aWeights[i] = a * myWeights[i] + (1. - a) * myWeights[i - 1];
    }
  }

  return update(::std::move(aPoles), ::std::move(aWeights), ::std::move(aKnots),
                ::std::move(aMults), myDegree);
}

Naive_Bool NurbsCurve::isValid() const { return myDegree > 0; }

Naive_NAMESPACE_END(geometry);
