#include <naivecgl/Geometry2d/NurbsCurve.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Polynomial.h>

Naive_NAMESPACE_BEGIN(geometry2d);

Naive_IMPLEMENT_RTTI(NurbsCurve);

NurbsCurve::NurbsCurve() noexcept
    : myDegree(0), myRational(Naive_False), myPeriodic(Naive_False) {}

NurbsCurve::NurbsCurve(const Naive_Pnt2dList1 &thePoles,
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

Naive_Code NurbsCurve::Init(const Naive_Pnt2dList1 &thePoles,
                            const Naive_RealList1 &theWeights,
                            const Naive_RealList1 &theKnots,
                            const Naive_IntegerList1 &theMults,
                            const Naive_Integer theDegree,
                            const Naive_Bool thePeriodic) noexcept {
  if (thePoles.size() != theWeights.size())
    return Naive_Code_poles_weights_not_match;

  Naive_XYZList1 theCPs{};
  theCPs.reserve(thePoles.size());
  for (Naive_Integer i = 0; i < thePoles.size(); ++i) {
    theCPs.push_back(thePoles[i].HomoCoord() * theWeights[i]);
  }

  return update(::std::move(theCPs), theKnots, theMults, theDegree,
                thePeriodic);
}

Naive_Code NurbsCurve::Init(const Naive_NurbsCurve_sf_t &theSF) noexcept {
  int degree = theSF.degree;
  int n_vertices = theSF.n_vertices;
  int vertex_dim = theSF.vertex_dim;
  double *vertex = theSF.vertex;
  int n_knots = theSF.n_knots;
  double *knot = theSF.knot;
  int *knot_mult = theSF.knot_mult;

  if (!vertex || !knot || !knot_mult)
    return Naive_Code_invalid_value;

  if (n_knots < 2)
    return Naive_Code_insufficient_knots;

  if (degree < 1)
    return Naive_Code_value_out_of_range;

  Naive_Integer nbCPs = n_vertices / vertex_dim;
  if (nbCPs < 2)
    return Naive_Code_insufficient_points;

  Naive_XYZList1 aCPs(nbCPs);

  if (theSF.is_rational && vertex_dim == 3) {
    for (Naive_XYZ &aCP : aCPs) {
      aCP.x() = *(vertex++);
      aCP.y() = *(vertex++);
      aCP.z() = *(vertex++);
    }
  } else if (!theSF.is_rational && vertex_dim == 2) {
    for (Naive_XYZ &aCP : aCPs) {
      aCP.x() = *(vertex++);
      aCP.y() = *(vertex++);
      aCP.z() = 1.;
    }
  } else {
    return Naive_Code_bad_dimension;
  }

  Naive_RealList1 aKnots(knot, knot + n_knots);
  Naive_IntegerList1 aMults(knot_mult, knot_mult + n_knots);

  return update(::std::move(aCPs), ::std::move(aKnots), ::std::move(aMults),
                degree, theSF.is_periodic);
}

Naive_Bool NurbsCurve::IsValid() const { return myDegree > 0; }

Handle_Naive_Geometry2d NurbsCurve::Clone() const {
  return new NurbsCurve(*this);
}

Naive_Integer NurbsCurve::NbPoles() const {
  return IsValid() ? static_cast<Naive_Integer>(myCPs.size()) : 0;
}

Naive_Pnt2d NurbsCurve::Pole(const Naive_Integer theIndex) const {
  Naive_Pnt2d aPole{};
  if (theIndex >= 0 && theIndex < NbPoles()) {
    aPole.HomoCoord(myCPs[theIndex]);
  }
  return aPole;
}

Naive_Pnt2dList1 NurbsCurve::Poles() const {
  if (!IsValid())
    return {};

  Naive_Pnt2dList1 aPoles(myCPs.size(), Naive_Pnt2d{});
  for (Naive_Integer i = 0; i < myCPs.size(); ++i) {
    aPoles[i].HomoCoord(myCPs[i]);
  }
  return aPoles;
}

Naive_Real NurbsCurve::Weight(const Naive_Integer theIndex) const {
  if (theIndex < 0 || theIndex >= NbPoles())
    return math::Constant::UnsetReal();
  return myCPs[theIndex].z();
}

Naive_RealList1 NurbsCurve::Weights() const {
  if (!IsValid())
    return {};

  Naive_RealList1 aWeights(myCPs.size(), 0.);
  for (Naive_Integer i = 0; i < myCPs.size(); ++i) {
    aWeights[i] = myCPs[i].z();
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

Naive_Pnt2d NurbsCurve::PointAt(const Naive_Real theT) const {
  Naive_Vec2dList1 aD{};
  if (Evaluate(theT, 0, aD) != Naive_Code_ok)
    return Naive_Pnt2d::Unset();
  return aD[0].XY();
}

Naive_Vec2d NurbsCurve::TangentAt(const Naive_Real theT) const {
  Naive_Vec2dList1 aD{};
  if (Evaluate(theT, 1, aD) != Naive_Code_ok)
    return Naive_Vec2d::Unset();
  return aD[1];
}

Naive_Code NurbsCurve::Evaluate(const Naive_Real theT, const Naive_Integer theN,
                                Naive_Vec2dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  return math::Nurbs::CurveEvaluate<Naive_Vec2d, 2>(
      myCPs, myFlatKnots, myKnots, myMults, myDegree, theT, theN, theD);
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

Naive_Code NurbsCurve::RaiseDegree(const Naive_Integer theDegree) {
  Naive_XYZList1 aCPs{};
  Naive_RealList1 aKnots{};
  Naive_IntegerList1 aMults{};

  Naive_Code aCode = math::Nurbs::CurveRaiseDegree<2>(
      myCPs, myFlatKnots, myKnots, myMults, myDegree, theDegree, aCPs, aKnots,
      aMults);

  if (aCode != Naive_Code_ok)
    return aCode;

  return update(::std::move(aCPs), ::std::move(aKnots), ::std::move(aMults),
                myDegree, myPeriodic);
}

Naive_Code NurbsCurve::IncreaseMultiplicity(const Naive_Integer theI,
                                            const Naive_Integer theM) {
  Naive_XYZList1 aCPs{};
  Naive_RealList1 aKnots{};
  Naive_IntegerList1 aMults{};

  Naive_Code aCode = math::Nurbs::CurveIncreaseMultiplicity<2>(
      myCPs, myFlatKnots, myKnots, myMults, myDegree, theI, theM, aCPs, aKnots,
      aMults);

  if (aCode != Naive_Code_ok)
    return aCode;

  return update(::std::move(aCPs), ::std::move(aKnots), ::std::move(aMults),
                myDegree, myPeriodic);
}

Naive_Code NurbsCurve::InsertKnot(const Naive_Real theT,
                                  const Naive_Integer theM) {
  Naive_XYZList1 aCPs{};
  Naive_RealList1 aKnots{};
  Naive_IntegerList1 aMults{};

  Naive_Code aCode = math::Nurbs::CurveInsertKnot<2>(
      myCPs, myFlatKnots, myKnots, myMults, myDegree, theT, theM, aCPs, aKnots,
      aMults);

  if (aCode != Naive_Code_ok)
    return aCode;

  return update(::std::move(aCPs), ::std::move(aKnots), ::std::move(aMults),
                myDegree, myPeriodic);
}

Naive_Code NurbsCurve::RemoveKnot(const Naive_Integer theI,
                                  const Naive_Integer theM) {
  Naive_XYZList1 aCPs{};
  Naive_RealList1 aKnots{};
  Naive_IntegerList1 aMults{};

  Naive_Code aCode = math::Nurbs::CurveRemoveKnot<2>(
      myCPs, myFlatKnots, myKnots, myMults, myDegree, theI, theM, aCPs, aKnots,
      aMults);

  if (aCode != Naive_Code_ok)
    return aCode;

  return update(::std::move(aCPs), ::std::move(aKnots), ::std::move(aMults),
                myDegree, myPeriodic);
}

Naive_Pnt2d NurbsCurve::EndPoint() const {
  if (!IsValid())
    return Naive_Pnt2d::Unset();

  if (myMults[myMults.size() - 1] == myDegree + 1) {
    Naive_Pnt2d aP{};
    aP.HomoCoord(myCPs[myCPs.size() - 1]);
    return aP;
  }

  return PointAt(LastParameter());
}

Naive_Pnt2d NurbsCurve::StartPoint() const {
  if (!IsValid())
    return Naive_Pnt2d::Unset();

  if (myMults[0] == myDegree + 1) {
    Naive_Pnt2d aP{};
    aP.HomoCoord(myCPs[0]);
    return aP;
  }

  return PointAt(FirstParameter());
}

Naive_Bool NurbsCurve::IsPeriodic() const { return myPeriodic; }

Naive_Real NurbsCurve::Period() const { return math::Constant::UnsetReal(); }

Naive_Code NurbsCurve::Dump(Naive_NurbsCurve_sf_t &theSF,
                            const common::MemHandler &theHandler) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  theSF.degree = Degree();
  theSF.vertex_dim = IsRational() ? 3 : 2;
  theSF.is_rational = IsRational();
  theSF.form = Naive_NurbsCurve_form_unset_c;
  theSF.is_periodic = IsPeriodic();
  theSF.is_closed = IsClosed();
  theSF.n_vertices = theSF.vertex_dim * static_cast<int>(myCPs.size());
  theSF.n_knots = static_cast<int>(myKnots.size());
  theSF.vertex = nullptr;
  theSF.knot = nullptr;
  theSF.knot_mult = nullptr;

  Naive_Code aCode = Naive_Code_ok;

  aCode = theHandler.Allocator(theSF.n_vertices * sizeof(double),
                               (void **)&(theSF.vertex));
  if (aCode != Naive_Code_ok)
    goto CLEAN;
  aCode = theHandler.Allocator(theSF.n_knots * sizeof(double),
                               (void **)&(theSF.knot));
  if (aCode != Naive_Code_ok)
    goto CLEAN;
  aCode = theHandler.Allocator(theSF.n_knots * sizeof(int),
                               (void **)&(theSF.knot_mult));
  if (aCode != Naive_Code_ok)
    goto CLEAN;

  double *p_vertex = theSF.vertex;

  if (IsRational()) {
    for (const Naive_XYZ &aCP : myCPs) {
      *(p_vertex++) = aCP.x();
      *(p_vertex++) = aCP.y();
      *(p_vertex++) = aCP.z();
    }
  } else {
    for (const Naive_XYZ &aCP : myCPs) {
      *(p_vertex++) = aCP.x();
      *(p_vertex++) = aCP.y();
    }
  }

  ::std::copy(myKnots.cbegin(), myKnots.cend(), theSF.knot);
  ::std::copy(myMults.cbegin(), myMults.cend(), theSF.knot_mult);

  return Naive_Code_ok;

CLEAN:
  theHandler.Deleter(theSF.vertex);
  theHandler.Deleter(theSF.knot);
  theHandler.Deleter(theSF.knot_mult);
  theSF.vertex = nullptr;
  theSF.knot = nullptr;
  theSF.knot_mult = nullptr;
  return aCode;
}

Naive_NAMESPACE_END(geometry2d);
