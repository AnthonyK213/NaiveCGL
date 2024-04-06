#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Math/Util.h>

#include <numeric>

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

  if (theKnots.size() < 2)
    return;

  if (theKnots.size() != theMults.size())
    return;

  for (Naive_Integer i = 0; i < theMults.size(); ++i) {
    if (theMults[i] < 1)
      return;

    if (i != 0 && i != theMults.size() - 1) {
      if (theMults[i] > theDegree)
        return;
    } else if (theMults[i] > theDegree + 1) {
      return;
    }
  }

  for (Naive_Integer i = 1; i < theKnots.size(); ++i) {
    if (theKnots[i] <= theKnots[i - 1])
      return;
  }

  mySpanIdx.reserve(theMults.size() - 1);
  Naive_Integer nbFlatKnots = theMults[0];
  for (Naive_Integer i = 1; i < theMults.size(); ++i) {
    mySpanIdx.push_back(nbFlatKnots);
    nbFlatKnots += theMults[i];
  }

  if (thePoles.size() + theDegree + 1 == nbFlatKnots)
    myPeriodic = false;
  else if (thePoles.size() == nbFlatKnots)
    // TODO: What is periodic?
    myPeriodic = true;
  else
    return;

  myPoles = thePoles;
  myWeights = theWeights;
  myKnots = theKnots;
  myMults = theMults;
  myDegree = theDegree;

  for (Naive_Integer i = 1; i < myWeights.size(); ++i) {
    if (!math::EpsilonEquals(myWeights[i], myWeights[0])) {
      myRational = true;
      break;
    }
  }

  myFlatKnots.reserve(nbFlatKnots);
  for (Naive_Integer i = 0; i < theKnots.size(); ++i) {
    for (Naive_Integer j = 0; j < theMults[i]; ++j) {
      myFlatKnots.push_back(theKnots[i]);
    }
  }
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

  Naive_Integer iSpan = findSpan(theT);
  if (iSpan < 0)
    return Naive_Point3d::Unset();

  // TODO: Caching.

  Naive_XYZ aXYZ(0., 0., 0.);
  Naive_Real aR = 0.;
  for (Naive_Integer i = (::std::max)(0, iSpan - myDegree); i <= iSpan; ++i) {
    Naive_Real aN = myWeights[i] * basisFn(i, myDegree, theT, iSpan);
    aXYZ += aN * myPoles[i].XYZ();
    aR += aN;
  }

  aXYZ /= aR;
  return aXYZ;
}

Naive_Vector3d NurbsCurve::TangentAt(const Naive_Real theT) const {
  return Naive_Vector3d::Unset();
}

Naive_Bool NurbsCurve::DerivativeAt(const Naive_Real theT,
                                    const Naive_Integer theN,
                                    Naive_Vector3dList &theD) const {
  return true;
}

Naive_Bool NurbsCurve::isValid() const { return myDegree > 0; }

Naive_Integer NurbsCurve::findSpan(const Naive_Real theT) const {
  if (theT < FirstParameter() || theT > LastParameter())
    return -1;

  Naive_Integer m = static_cast<Naive_Integer>(myKnots.size()) - 1;
  Naive_Integer k;
  if (theT == LastParameter()) {
    k = m - 1;
  } else {
    Naive_Integer lower = 0;
    Naive_Integer upper = m;
    while (upper - lower > 1) {
      Naive_Integer mid = (lower + upper) >> 1;
      if (theT < myKnots[mid])
        upper = mid;
      else
        lower = mid;
    }
    k = lower;
  }

  return mySpanIdx[k] - 1;
}

Naive_Real NurbsCurve::basisFn(Naive_Integer theI, Naive_Integer theP,
                               Naive_Real theT, Naive_Integer theSpan) const {
  if (theP == 0)
    return theSpan == theI ? 1. : 0.;

  Naive_Real aF0 = myFlatKnots[theI + theP] - myFlatKnots[theI];
  Naive_Real aG0 = myFlatKnots[theI + theP + 1] - myFlatKnots[theI + 1];
  Naive_Real aF =
      math::EpsilonEquals(aF0, 0.) ? 0. : (theT - myFlatKnots[theI]) / aF0;
  Naive_Real aG = math::EpsilonEquals(aG0, 0.)
                      ? 0.
                      : (myFlatKnots[theI + theP + 1] - theT) / aG0;

  return aF * basisFn(theI, theP - 1, theT, theSpan) +
         aG * basisFn(theI + 1, theP - 1, theT, theSpan);
}

Naive_NAMESPACE_END(geometry);
