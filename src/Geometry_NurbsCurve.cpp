#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Math/Nurbs.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

NurbsCurve::NurbsCurve(const Naive_Point3dList &thePoles,
                       const Naive_RealList &theWeights,
                       const Naive_RealList &theKnots,
                       const Naive_IntegerList &theMults,
                       const Naive_Integer theDegree)
    : myRational(false), myPeriodic(false), myDegree(0), myFlatKnots(),
      mySpanIdx() {
  if (theDegree < 1)
    return;

  if (thePoles.size() < 2)
    return;

  if (thePoles.size() != theWeights.size())
    return;

  if (!math::Nurbs::CheckParam(thePoles.size(), theKnots, theMults, theDegree,
                               myPeriodic, myFlatKnots, mySpanIdx))
    return;

  for (Naive_Integer i = 1; i < theWeights.size(); ++i) {
    if (!math::Util::EpsilonEquals(theWeights[i], theWeights[0])) {
      myRational = true;
      break;
    }
  }

  myPoles = thePoles;
  myWeights = theWeights;
  myKnots = theKnots;
  myMults = theMults;
  myDegree = theDegree;
}

Naive_Integer NurbsCurve::NbPoles() const {
  return static_cast<Naive_Integer>(myPoles.size());
}

const Naive_Point3d &NurbsCurve::Pole(const Naive_Integer theIndex) const {
  return myPoles.at(theIndex);
}

const Naive_Point3dList &NurbsCurve::Poles() const { return myPoles; }

Naive_EXPORT Naive_Real NurbsCurve::Weight(const Naive_Integer theIndex) const {
  return myWeights.at(theIndex);
}

const Naive_RealList &NurbsCurve::Weights() const { return myWeights; }

Naive_Integer NurbsCurve::NbKnots() const {
  return static_cast<Naive_Integer>(myKnots.size());
}

Naive_Real NurbsCurve::Knot(const Naive_Integer theIndex) const {
  return myKnots.at(theIndex);
}

const Naive_RealList &NurbsCurve::Knots() const { return myKnots; }

Naive_Real NurbsCurve::FirstParameter() const { return myKnots.at(0); }

Naive_Real NurbsCurve::LastParameter() const {
  return myKnots.at(myKnots.size() - 1);
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

Naive_Bool NurbsCurve::InsertKnot(const Naive_Real theU,
                                  const Naive_Integer theM) {
  if (theM <= 0 || theM > Degree())
    return false;

  Naive_Integer iSpan = math::Nurbs::FindSpan(myKnots, theU);
  if (iSpan < 0)
    return false;

  // FIXME: Float equality?

  if (theU == myKnots[iSpan])
    return IncreaseMultiplicity(iSpan, theM);

  if (theU == myKnots[iSpan + 1])
    return IncreaseMultiplicity(iSpan + 1, theM);

  return true;
}

Naive_Bool NurbsCurve::isValid() const { return myDegree > 0; }

Naive_NAMESPACE_END(geometry);
