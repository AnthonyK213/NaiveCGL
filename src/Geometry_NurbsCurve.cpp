#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Polynomial.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(NurbsCurve);

NurbsCurve::NurbsCurve() noexcept
    : myDegree(0), myRational(Naive_False), myPeriodic(Naive_False) {}

NurbsCurve::NurbsCurve(const Naive_Pnt3dList1 &thePoles,
                       const Naive_RealList1 &theWeights,
                       const Naive_RealList1 &theKnots,
                       const Naive_IntegerList1 &theMults,
                       const Naive_Integer theDegree,
                       const Naive_Bool thePeriodic) noexcept
    : myDegree(0), myRational(Naive_False), myPeriodic(Naive_False) {
  Init(thePoles, theWeights, theKnots, theMults, theDegree, thePeriodic);
}

NurbsCurve::NurbsCurve(const Naive_NurbsCurve_sf_t &theSF) noexcept
    : myDegree(0), myRational(Naive_False), myPeriodic(Naive_False) {
  Init(theSF);
}

Naive_Code NurbsCurve::Init(const Naive_Pnt3dList1 &thePoles,
                            const Naive_RealList1 &theWeights,
                            const Naive_RealList1 &theKnots,
                            const Naive_IntegerList1 &theMults,
                            const Naive_Integer theDegree,
                            const Naive_Bool thePeriodic) noexcept {
  if (thePoles.size() != theWeights.size())
    return Naive_Code_poles_weights_not_match;

  Naive_XYZWList1 theCPs{};
  theCPs.reserve(thePoles.size());
  for (Naive_Integer i = 0; i < thePoles.size(); ++i) {
    theCPs.push_back(thePoles[i].HomoCoord() * theWeights[i]);
  }

  return update(::std::move(theCPs), theKnots, theMults, theDegree,
                thePeriodic);
}

Naive_Code NurbsCurve::Init(const Naive_NurbsCurve_sf_t &theSF) noexcept {
  return Naive_Code_not_implemented;
}

Naive_Bool NurbsCurve::IsValid() const { return myDegree > 0; }

Handle_Naive_Geometry NurbsCurve::Clone() const {
  return new NurbsCurve(*this);
}

Naive_Integer NurbsCurve::NbPoles() const {
  return IsValid() ? static_cast<Naive_Integer>(myCPs.size()) : 0;
}

Naive_Pnt3d NurbsCurve::Pole(const Naive_Integer theIndex) const {
  Naive_Pnt3d aPole{};
  if (theIndex >= 0 && theIndex < NbPoles()) {
    aPole.HomoCoord(myCPs[theIndex]);
  }
  return aPole;
}

Naive_Pnt3dList1 NurbsCurve::Poles() const {
  if (!IsValid())
    return {};

  Naive_Pnt3dList1 aPoles(myCPs.size(), Naive_Pnt3d{});
  for (Naive_Integer i = 0; i < myCPs.size(); ++i) {
    aPoles[i].HomoCoord(myCPs[i]);
  }
  return aPoles;
}

Naive_Real NurbsCurve::Weight(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbPoles())
    return math::Constant::UnsetReal();
  return myCPs[theIndex].w();
}

Naive_RealList1 NurbsCurve::Weights() const {
  if (!IsValid())
    return {};

  Naive_RealList1 aWeights(myCPs.size(), 0.);
  for (Naive_Integer i = 0; i < myCPs.size(); ++i) {
    aWeights[i] = myCPs[i].w();
  }
  return aWeights;
}

Naive_Integer NurbsCurve::NbKnots() const {
  return IsValid() ? static_cast<Naive_Integer>(myKnots.size()) : 0;
}

Naive_Real NurbsCurve::Knot(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbKnots())
    return math::Constant::UnsetReal();
  return myKnots[theIndex];
}

Naive_Integer NurbsCurve::Multiplicity(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbKnots())
    return 0;
  return myMults[theIndex];
}

Naive_Real NurbsCurve::FirstParameter() const {
  return IsValid() ? myKnots[0] : math::Constant::UnsetReal();
}

Naive_Real NurbsCurve::LastParameter() const {
  return IsValid() ? myKnots[myKnots.size() - 1] : math::Constant::UnsetReal();
}

Naive_Code NurbsCurve::Evaluate(const Naive_Real theT, const Naive_Integer theN,
                                Naive_Vec3dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  return math::Nurbs::EvaluateCurve<Naive_Vec3d, 3>(myCPs, myFlatKnots, myKnots,
                                                    myMults, theT, theN, theD);
}

Naive_Code NurbsCurve::CurvatureAt(const Naive_Real theT,
                                   Naive_Vec3d &theV) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  Naive_Code aCode = Naive_Code_ok;

  Naive_Vec3dList1 aD{};
  aCode = Evaluate(theT, 2, aD);
  if (aCode)
    return aCode;

  Naive_Vec3d b = aD[1].Crossed(aD[2]);
  Naive_Real k = b.Length() / ::std::pow(aD[1].Length(), 3);
  theV = b.Crossed(aD[1]).Normalized().Multiplied(k);
  return aCode;
}

Naive_Code NurbsCurve::RaiseDegree(const Naive_Integer theDegree) {
  if (!IsValid())
    return Naive_Code_invalid_object;

  if (theDegree < 0)
    return Naive_Code_value_out_of_range;

  return Naive_Code_not_implemented;
}

Naive_Code NurbsCurve::IncreaseMultiplicity(const Naive_Integer theI,
                                            const Naive_Integer theM) {
  // if (theI < 0 || theI >= myMults.size() || theM < 0)
  //   return Naive_Code_value_out_of_range;

  // if (theM == 0)
  //   return Naive_Code_ok;

  // Naive_Real T = myKnots[theI];
  // Naive_Integer S = myMults[theI];

  // if (theI != 0 && theI != myMults.size() - 1) {
  //   if (theM + S > myDegree)
  //     return Naive_Code_value_out_of_range;
  // } else if (theM + S > myDegree + 1)
  //   return Naive_Code_value_out_of_range;

  // /* The last knot belongs to the last span. */
  // Naive_Integer iSpan = (theI == myMults.size() - 1) ? theI - 1 : theI;
  // Naive_Integer K = mySpanIdx[iSpan] - 1;

  // Naive_Pnt3dList1 aPoles(myPoles.size() + theM, Naive_Pnt3d::Unset());
  // Naive_RealList1 aWeights(myWeights.size() + theM,
  //                          math::Constant::UnsetReal());
  // Naive_IntegerList1 aMults = myMults;
  // aMults[theI] += theM;

  // for (Naive_Integer I = 0; I < aPoles.size(); ++I) {
  //   Naive_XYZW q = math::Nurbs::PoleAfterInsertKnot<3>(
  //       myPoles, myWeights, myFlatKnots, myDegree, T, K, S, I, theM);
  //   aPoles[I].HomoCoord(q);
  //   aWeights[I] = q(3);
  // }

  // return update(::std::move(aPoles), ::std::move(aWeights), myKnots,
  //               ::std::move(aMults), myDegree);

  return Naive_Code_not_implemented;
}

Naive_Code NurbsCurve::InsertKnot(const Naive_Real theT,
                                  const Naive_Integer theM) {
  // if (theM < 0 || theM > Degree())
  //   return Naive_Code_value_out_of_range;

  // Naive_Integer iSpan = math::Nurbs::FindSpan(myKnots, theT);
  // if (iSpan < 0)
  //   return Naive_Code_value_out_of_range;
  // Naive_Integer K = mySpanIdx[iSpan] - 1;

  // if (theM == 0)
  //   return Naive_Code_ok;

  // /* If |theT| is already in the |myKnots|, the operation would be a
  //  * multiplicity increase. */

  // /* FIXME: Float equality? */

  // if (theT == myKnots[iSpan])
  //   return IncreaseMultiplicity(iSpan, theM);

  // if (theT == myKnots[iSpan + 1])
  //   return IncreaseMultiplicity(iSpan + 1, theM);

  // /* Makes no sense for a inner knot with a multiplicity greater than
  //  * |myDegree|. */

  // if (iSpan != 0 && iSpan != myMults.size() - 1) {
  //   if (theM > myDegree)
  //     return Naive_Code_value_out_of_range;
  // } else if (theM > myDegree + 1)
  //   return Naive_Code_value_out_of_range;

  // Naive_Pnt3dList1 aPoles(myPoles.size() + theM, Naive_Pnt3d::Unset());
  // Naive_RealList1 aWeights(myWeights.size() + theM,
  //                          math::Constant::UnsetReal());
  // Naive_RealList1 aKnots = myKnots;
  // Naive_IntegerList1 aMults = myMults;
  // aKnots.insert(aKnots.begin() + iSpan + 1, theT);
  // aMults.insert(aMults.begin() + iSpan + 1, theM);

  // for (Naive_Integer I = 0; I < aPoles.size(); ++I) {
  //   Naive_XYZW q = math::Nurbs::PoleAfterInsertKnot<3>(
  //       myPoles, myWeights, myFlatKnots, myDegree, theT, K, 0, I, theM);
  //   aPoles[I].HomoCoord(q);
  //   aWeights[I] = q(3);
  // }

  // return update(::std::move(aPoles), ::std::move(aWeights),
  // ::std::move(aKnots),
  //               ::std::move(aMults), myDegree);

  return Naive_Code_not_implemented;
}

Naive_Code NurbsCurve::RemoveKnot(const Naive_Integer theI,
                                  const Naive_Integer theM) {
  // Naive_Integer S = Multiplicity(theI);
  // if (S == 0)
  //   return Naive_Code_index_out_of_range;

  // Naive_Integer R = mySpanIdx[theI] - 1;
  // Naive_Integer N = S - theM;

  // if (theM < 0 || N < 0)
  //   return Naive_Code_value_out_of_range;

  // /* Nothing to do... */
  // if (N == 0)
  //   return Naive_Code_ok;

  // Naive_Integer aFirst = R - S;
  // Naive_Integer aLast = R - Degree();

  // for (Naive_Integer t = 0; t < N; ++t) {
  // }

  return Naive_Code_not_implemented;
}

Naive_Pnt3d NurbsCurve::EndPoint() const {
  if (!IsValid())
    return Naive_Pnt3d::Unset();

  if (myMults[myMults.size() - 1] == myDegree + 1) {
    Naive_Pnt3d aP{};
    aP.HomoCoord(myCPs[myCPs.size() - 1]);
    return aP;
  }

  return PointAt(LastParameter());
}

Naive_Pnt3d NurbsCurve::StartPoint() const {
  if (!IsValid())
    return Naive_Pnt3d::Unset();

  if (myMults[0] == myDegree + 1) {
    Naive_Pnt3d aP{};
    aP.HomoCoord(myCPs[0]);
    return aP;
  }

  return PointAt(FirstParameter());
}

Naive_Bool NurbsCurve::IsPeriodic() const { return myPeriodic; }

Naive_Real NurbsCurve::Period() const { return math::Constant::UnsetReal(); }

Naive_Code NurbsCurve::Dump(Naive_NurbsCurve_sf_t &theSF) const {
  return Naive_Code_not_implemented;
}

Naive_Code NurbsCurve::transform(const Naive_Trsf3d &theTrsf) {
  return Naive_Code_not_implemented;
}

Naive_NAMESPACE_END(geometry);
