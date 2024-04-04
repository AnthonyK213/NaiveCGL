#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Math/Util.h>

#include <numeric>

Naive_NAMESPACE_BEGIN(geometry);

NurbsCurve::NurbsCurve(const Naive_Point3dList &thePoles,
                       const Naive_RealList &theWeights,
                       const Naive_RealList &theKnots,
                       const Naive_IntegerList &theMults,
                       const Naive_Integer theDegree)
    : myRational(false), myPeriodic(false), myDegree(0), myFlatKnots() {
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

  for (Naive_Integer i = 0; i < theWeights.size(); ++i) {
    if (theWeights[i] < 1 || theWeights[i] > theDegree)
      return;
  }

  for (Naive_Integer i = 1; i < theKnots.size(); ++i) {
    if (theKnots[i] < theKnots[i - 1])
      return;
  }

  Naive_Integer nbFlatKnots =
      std::accumulate(theMults.cbegin(), theMults.cend(), 0);

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

const Naive_Point3d &NurbsCurve::Pole(const Naive_Integer theIndex) const {
  return myPoles.at(theIndex);
}

const Naive_Point3dList &NurbsCurve::Poles() const { return myPoles; }

Naive_EXPORT Naive_Real NurbsCurve::Weight(const Naive_Integer theIndex) const {
  return myWeights.at(theIndex);
}

const Naive_RealList &NurbsCurve::Weights() const { return myWeights; }

Naive_Real NurbsCurve::Knot(const Naive_Integer theIndex) const {
  return myKnots.at(theIndex);
}

const Naive_RealList &NurbsCurve::Knots() const { return myKnots; }

Naive_Point3d NurbsCurve::PointAt(const Naive_Real theT) const {
  return Naive_Point3d::Unset();
}

Naive_Vector3d NurbsCurve::TangentAt(const Naive_Real theT) const {
  return Naive_Vector3d::Unset();
}

Naive_Bool NurbsCurve::DerivativeAt(const Naive_Real theT,
                                    const Naive_Integer theN,
                                    Naive_Vector3dList &theD) const {
  return true;
}

Naive_NAMESPACE_END(geometry);
