#include <naivecgl/Geometry2d/NurbsCurve.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Polynomial.h>

Naive_NAMESPACE_BEGIN(geometry2d);

NurbsCurve::NurbsCurve() noexcept
    : myDegree(0), myRational(Naive_False), myPeriodic(Naive_False),
      myFlatKnots(), mySpanIdx() {}

NurbsCurve::NurbsCurve(const Naive_Pnt2dList1 &thePoles,
                       const Naive_RealList1 &theWeights,
                       const Naive_RealList1 &theKnots,
                       const Naive_IntegerList1 &theMults,
                       const Naive_Integer theDegree) noexcept
    : myDegree(0), myRational(Naive_False), myPeriodic(Naive_False),
      myFlatKnots(), mySpanIdx() {
  Init(thePoles, theWeights, theKnots, theMults, theDegree);
}

Naive_Code NurbsCurve::Init(const Naive_Pnt2dList1 &thePoles,
                            const Naive_RealList1 &theWeights,
                            const Naive_RealList1 &theKnots,
                            const Naive_IntegerList1 &theMults,
                            const Naive_Integer theDegree) noexcept {
  return update(thePoles, theWeights, theKnots, theMults, theDegree);
}

Naive_Bool NurbsCurve::IsValid() const { return myDegree > 0; }

Handle_Naive_Geometry2d NurbsCurve::Clone() const {
  return new NurbsCurve(*this);
}

Naive_Integer NurbsCurve::NbPoles() const {
  if (!IsValid())
    return 0;
  return static_cast<Naive_Integer>(myPoles.size());
}

const Naive_Pnt2d &NurbsCurve::Pole(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbPoles() || !IsValid())
    return Naive_Pnt2d::Unset();
  return myPoles[theIndex];
}

Naive_EXPORT Naive_Real NurbsCurve::Weight(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbPoles() || !IsValid())
    return math::Constant::UnsetReal();
  return myWeights[theIndex];
}

Naive_Integer NurbsCurve::NbKnots() const {
  if (!IsValid())
    return 0;
  return static_cast<Naive_Integer>(myKnots.size());
}

Naive_Real NurbsCurve::Knot(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbKnots() || !IsValid())
    return math::Constant::UnsetReal();
  return myKnots[theIndex];
}

Naive_Integer NurbsCurve::Multiplicity(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbKnots() || !IsValid())
    return 0;
  return myMults[theIndex];
}

Naive_Real NurbsCurve::FirstParameter() const {
  if (!IsValid())
    return math::Constant::UnsetReal();
  return myKnots[0];
}

Naive_Real NurbsCurve::LastParameter() const {
  if (!IsValid())
    return math::Constant::UnsetReal();
  return myKnots[myKnots.size() - 1];
}

Naive_Pnt2d NurbsCurve::PointAt(const Naive_Real theT) const {
  Naive_Vec2dList1 aD{};
  if (!Evaluate(theT, 0, aD))
    return Naive_Pnt2d::Unset();
  return aD[0].XY();
}

Naive_Vec2d NurbsCurve::TangentAt(const Naive_Real theT) const {
  Naive_Vec2dList1 aD{};
  if (!Evaluate(theT, 1, aD))
    return Naive_Vec2d::Unset();
  return aD[1];
}

Naive_Code NurbsCurve::Evaluate(const Naive_Real theT, const Naive_Integer theN,
                                Naive_Vec2dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  if (theN < 0)
    return Naive_Code_value_out_of_range;

  Naive_Integer iSpan = math::Nurbs::FindFlatSpan(myKnots, mySpanIdx, theT);
  if (iSpan < 0)
    return Naive_Code_value_out_of_range;

  Naive_RealList1 aWBuf(theN + 1, math::Constant::UnsetReal());
  theD.resize(theN + 1, Naive_Vec2d::Unset());
  Naive_List1<math::Polynomial> anA{};
  anA.reserve(Degree() + 1);
  Naive_Integer pBegin = (::std::max)(0, iSpan - Degree());
  Naive_Integer pEnd = iSpan;
  for (Naive_Integer i = pBegin; i <= pEnd; ++i) {
    auto b = math::Nurbs::BasisFn(myFlatKnots, i, Degree(), iSpan);
    anA.emplace_back(::std::move(b));
  }

  for (Naive_Integer I = 0; I <= theN; ++I) {
    Naive_XY A{0., 0.};
    Naive_Real W = 0.0;
    for (Naive_Integer k = pBegin; k <= pEnd; ++k) {
      Naive_Real N =
          anA[k - pBegin].Derivative(I).Evaluate(theT) * myWeights[k];
      A += N * myPoles[k].XY();
      W += N;
    }

    aWBuf[I] = W;

    for (Naive_Integer k = 1; k <= I; ++k) {
      A -= static_cast<Naive_Real>(math::Util::Combination(I, k)) * aWBuf[k] *
           theD[I - k].XY();
    }

    theD[I].ChangeXY() = A / aWBuf[0];
  }

  return Naive_Code_ok;
}

Naive_Code NurbsCurve::CurvatureAt(const Naive_Real theT,
                                   Naive_Vec2d &theV) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  Naive_Code aCode = Naive_Code_ok;

  Naive_Vec2dList1 aD{};
  aCode = Evaluate(theT, 2, aD);
  if (aCode)
    return aCode;

  Naive_Real b = aD[1].Crossed(aD[2]);
  Naive_Real k = b / ::std::pow(aD[1].Length(), 3);
  theV.SetCoord(-aD[1].Y(), aD[1].X());
  theV.Normalize();
  theV.Multiply(k);
  return aCode;
}

Naive_Code NurbsCurve::IncreaseDegree(const Naive_Integer theDegree) {
  if (!IsValid())
    return Naive_Code_invalid_object;

  if (theDegree < 0)
    return Naive_Code_value_out_of_range;

  return Naive_Code_ok;
}

Naive_Code NurbsCurve::IncreaseMultiplicity(const Naive_Integer theI,
                                            const Naive_Integer theM) {
  if (theI < 0 || theI >= myMults.size() || theM < 0)
    return Naive_Code_value_out_of_range;

  if (theM == 0)
    return Naive_Code_ok;

  Naive_Real T = myKnots[theI];
  Naive_Integer S = myMults[theI];

  if (theI != 0 && theI != myMults.size() - 1) {
    if (theM + S > myDegree)
      return Naive_Code_value_out_of_range;
  } else if (theM + S > myDegree + 1)
    return Naive_Code_value_out_of_range;

  /* The last knot belongs to the last span. */
  Naive_Integer iSpan = (theI == myMults.size() - 1) ? theI - 1 : theI;
  Naive_Integer K = mySpanIdx[iSpan] - 1;

  Naive_Pnt2dList1 aPoles(myPoles.size() + theM, Naive_Pnt2d::Unset());
  Naive_RealList1 aWeights(myWeights.size() + theM,
                           math::Constant::UnsetReal());
  Naive_IntegerList1 aMults = myMults;
  aMults[theI] += theM;

  for (Naive_Integer I = 0; I < aPoles.size(); ++I) {
    Naive_XYZ q = math::Nurbs::PoleAfterInsertKnot<2>(
        myPoles, myWeights, myFlatKnots, myDegree, T, K, S, I, theM);
    aPoles[I].HomoCoord(q);
    aWeights[I] = q(2);
  }

  return update(::std::move(aPoles), ::std::move(aWeights), myKnots,
                ::std::move(aMults), myDegree);
}

Naive_Code NurbsCurve::InsertKnot(const Naive_Real theT,
                                  const Naive_Integer theM) {
  if (theM < 0 || theM > Degree())
    return Naive_Code_value_out_of_range;

  Naive_Integer iSpan = math::Nurbs::FindSpan(myKnots, theT);
  if (iSpan < 0)
    return Naive_Code_value_out_of_range;
  Naive_Integer K = mySpanIdx[iSpan] - 1;

  if (theM == 0)
    return Naive_Code_ok;

  /* If |theT| is already in the |myKnots|, the operation would be a
   * multiplicity increase. */

  // FIXME: Float equality?

  if (theT == myKnots[iSpan])
    return IncreaseMultiplicity(iSpan, theM);

  if (theT == myKnots[iSpan + 1])
    return IncreaseMultiplicity(iSpan + 1, theM);

  /* Makes no sense for a inner knot with a multiplicity greater than
   * |myDegree|. */

  if (iSpan != 0 && iSpan != myMults.size() - 1) {
    if (theM > myDegree)
      return Naive_Code_value_out_of_range;
  } else if (theM > myDegree + 1)
    return Naive_Code_value_out_of_range;

  Naive_Pnt2dList1 aPoles(myPoles.size() + theM, Naive_Pnt2d::Unset());
  Naive_RealList1 aWeights(myWeights.size() + theM,
                           math::Constant::UnsetReal());
  Naive_RealList1 aKnots = myKnots;
  Naive_IntegerList1 aMults = myMults;
  aKnots.insert(aKnots.begin() + iSpan + 1, theT);
  aMults.insert(aMults.begin() + iSpan + 1, theM);

  for (Naive_Integer I = 0; I < aPoles.size(); ++I) {
    Naive_XYZ q = math::Nurbs::PoleAfterInsertKnot<2>(
        myPoles, myWeights, myFlatKnots, myDegree, theT, K, 0, I, theM);
    aPoles[I].HomoCoord(q);
    aWeights[I] = q(2);
  }

  return update(::std::move(aPoles), ::std::move(aWeights), ::std::move(aKnots),
                ::std::move(aMults), myDegree);
}

Naive_Code NurbsCurve::RemoveKnot(const Naive_Integer theI,
                                  const Naive_Integer theM) {
  Naive_Integer S = Multiplicity(theI);
  if (S == 0)
    return Naive_Code_index_out_of_range;

  Naive_Integer R = mySpanIdx[theI] - 1;
  Naive_Integer N = S - theM;

  if (theM < 0 || N < 0)
    return Naive_Code_value_out_of_range;

  /* Nothing to do... */
  if (N == 0)
    return Naive_Code_ok;

  Naive_Integer aFirst = R - S;
  Naive_Integer aLast = R - Degree();

  for (Naive_Integer t = 0; t < N; ++t) {
  }

  return Naive_Code_ok;
}

Naive_Pnt2d NurbsCurve::EndPoint() const {
  if (!IsValid())
    return Naive_Pnt2d::Unset();

  if (myMults[myMults.size() - 1] == myDegree + 1)
    return myPoles[myPoles.size() - 1];
  else
    return PointAt(LastParameter());
}

Naive_Pnt2d NurbsCurve::StartPoint() const {
  if (!IsValid())
    return Naive_Pnt2d::Unset();

  if (myMults[0] == myDegree + 1)
    return myPoles[0];
  else
    return PointAt(FirstParameter());
}

Naive_NAMESPACE_END(geometry2d);
