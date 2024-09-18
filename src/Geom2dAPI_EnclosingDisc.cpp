#include <naivecgl/Geom2dAPI/EnclosingDisc.h>
#include <naivecgl/Math/Precision.h>

Naive_NAMESPACE_BEGIN(geom2d_api);

EnclosingDisc::EnclosingDisc() : myPoints(), myOrigin(), myR(0.) {}

void EnclosingDisc::ReBuild(const Naive_Pnt2dList1 &thePoints) {
  myPoints = thePoints;

  if (myPoints.empty()) {
    myOrigin = Naive_Pnt2d::Unset();
    return;
  }

  if (myPoints.size() == 1) {
    myOrigin = myPoints[0];
    myR = 0.;
    return;
  }

  minDisc();
}

Naive_Bool EnclosingDisc::Result(Naive_Pnt2d &theOrigin,
                                 Naive_Real &theR) const {
  if (!myOrigin.IsValid())
    return Naive_False;

  theOrigin = myOrigin;
  theR = myR;
  return Naive_True;
}

inline Naive_Bool EnclosingDisc::isInsideCircle(const Naive_Pnt2d &theP) {
  return (theP.XY() - myOrigin.XY()).norm() <= myR;
}

void EnclosingDisc::minDisc() {
  myOrigin = {(myPoints[0].XY() + myPoints[1].XY()) * .5};
  myR = (myPoints[0].XY() - myPoints[1].XY()).norm() * .5;

  for (Naive_Integer i = 2; i < myPoints.size(); ++i) {
    if (!isInsideCircle(myPoints[i])) {
      minDiscWithPoint(i);
    }
  }
}

void EnclosingDisc::minDiscWithPoint(const Naive_Integer theI) {
  myOrigin = {(myPoints[0].XY() + myPoints[theI].XY()) * .5};
  myR = (myPoints[0].XY() - myPoints[theI].XY()).norm() * .5;

  for (Naive_Integer j = 1; j < theI; ++j) {
    if (!isInsideCircle(myPoints[j])) {
      minDiscWith2Points(theI, j);
    }
  }
}

void EnclosingDisc::minDiscWith2Points(const Naive_Integer theI,
                                       const Naive_Integer theJ) {
  myOrigin = {(myPoints[theI].XY() + myPoints[theJ].XY()) * .5};
  myR = (myPoints[theI].XY() - myPoints[theJ].XY()).norm() * .5;

  for (Naive_Integer k = 0; k < theJ; ++k) {
    if (!isInsideCircle(myPoints[k])) {
      circle3Points(myPoints[theI], myPoints[theJ], myPoints[k]);
    }
  }
}

void EnclosingDisc::circle3Points(const Naive_Pnt2d &theA,
                                  const Naive_Pnt2d &theB,
                                  const Naive_Pnt2d &theC) {
  Naive_Real a1 = 2. * (theA.X() - theB.X());
  Naive_Real b1 = 2. * (theA.Y() - theB.Y());
  Naive_Real a2 = 2. * (theB.X() - theC.X());
  Naive_Real b2 = 2. * (theB.Y() - theC.Y());
  Naive_Real d = a1 * b2 - a2 * b1;

  if (::std::abs(d) < math::Precision::Epsilon0()) {
    myOrigin = Naive_Pnt2d::Unset();
    return;
  }

  Naive_Real c1 = theA.XY().squaredNorm() - theB.XY().squaredNorm();
  Naive_Real c2 = theB.XY().squaredNorm() - theC.XY().squaredNorm();
  Naive_Real dd = 1. / d;

  myOrigin.ChangeXY().x() = (c1 * b2 - c2 * b1) * dd;
  myOrigin.ChangeXY().y() = (a1 * c2 - a2 * c1) * dd;
  myR = (myOrigin.XY() - theA.XY()).norm();
}

Naive_NAMESPACE_END(geom2d_api);
