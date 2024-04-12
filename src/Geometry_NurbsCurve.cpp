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
  if (!isValid())
    return Naive_Point3d::Unset();

  Naive_Integer iSpan = math::Nurbs::FindSpan(myKnots, mySpanIdx, theT);
  if (iSpan < 0)
    return Naive_Point3d::Unset();

  // TODO: Caching.

  Naive_XYZ aXYZ(0., 0., 0.);
  Naive_Real aW = 0.;
  for (Naive_Integer i = (::std::max)(0, iSpan - Degree()); i <= iSpan; ++i) {
    Naive_Real aN = myWeights[i] * math::Nurbs::BasisFnValue(
                                       myFlatKnots, i, Degree(), theT, iSpan);
    aXYZ += aN * myPoles[i].XYZ();
    aW += aN;
  }

  aXYZ /= aW;
  return aXYZ;
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

  Naive_Integer iSpan = math::Nurbs::FindSpan(myKnots, mySpanIdx, theT);
  if (iSpan < 0)
    return false;

  Naive_RealList aWBuf(theN + 1, math::Constant::UnsetValue());
  theD.resize(theN + 1, Naive_Vector3d::Unset());
  Naive_List<math::Polynomial> anA{};
  Naive_Integer pBegin = (::std::max)(0, iSpan - Degree());
  Naive_Integer pEnd = iSpan;
  anA.reserve(pEnd = pBegin + 1);
  for (Naive_Integer i = pBegin; i <= pEnd; ++i) {
    auto b = math::Nurbs::BasisFn(myFlatKnots, i, Degree(), iSpan)
                 .Multiplied(myWeights[i]);
    anA.push_back(b);
  }

  if (!derivativeAt(theT, theN, 0, pBegin, pEnd, anA, aWBuf, theD))
    return false;

  return true;
}

Naive_Bool NurbsCurve::isValid() const { return myDegree > 0; }

Naive_Bool NurbsCurve::derivativeAt(
    const Naive_Real theT, const Naive_Integer theN, const Naive_Integer theI,
    const Naive_Integer thePBegin, const Naive_Integer thePEnd,
    const Naive_List<math::Polynomial> &theA, Naive_RealList &theWBuf,
    Naive_Vector3dList &theD) const {
  if (theI > theN)
    return true;

  Naive_XYZ A{0., 0., 0.};
  Naive_Real W = 0.0;
  for (Naive_Integer i = thePBegin; i <= thePEnd; ++i) {
    Naive_Real N = theA[i - thePBegin].Derivative(theI).Evaluate(theT);
    A += N * myPoles[i].XYZ();
    W += N;
  }

  theWBuf[theI] = W;

  for (Naive_Integer i = 1; i <= theI; ++i) {
    Naive_XYZ M = static_cast<Naive_Real>(math::Util::Combination(theI, i)) *
                  theWBuf[i] * theD[theI - i].XYZ();
    A -= M;
  }

  theD[theI].ChangeXYZ() = A / theWBuf[0];

  return derivativeAt(theT, theN, theI + 1, thePBegin, thePEnd, theA, theWBuf,
                      theD);
}

Naive_NAMESPACE_END(geometry);
