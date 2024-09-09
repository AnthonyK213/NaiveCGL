#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Polynomial.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(NurbsSurface);

NurbsSurface::NurbsSurface() noexcept
    : myUDegree(0), myVDegree(0), myURational(Naive_False),
      myVRational(Naive_False), myUPeriodic(Naive_False),
      myVPeriodic(Naive_False) {}

NurbsSurface::NurbsSurface(
    const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
    const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree,
    const Naive_Bool theUPeriodic, const Naive_Bool theVPeriodic) noexcept
    : myUDegree(0), myVDegree(0), myURational(Naive_False),
      myVRational(Naive_False), myUPeriodic(Naive_False),
      myVPeriodic(Naive_False) {
  Init(thePoles, theWeights, theUKnots, theVKnots, theUMults, theVMults,
       theUDegree, theVDegree, theUPeriodic, theVPeriodic);
}

NurbsSurface::NurbsSurface(const Naive_NurbsSurface_sf_t &theSF) noexcept
    : myUDegree(0), myVDegree(0), myURational(Naive_False),
      myVRational(Naive_False), myUPeriodic(Naive_False),
      myVPeriodic(Naive_False) {
  Init(theSF);
}

Naive_Code NurbsSurface::Init(
    const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
    const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree,
    const Naive_Bool theUPeriodic, const Naive_Bool theVPeriodic) noexcept {
  Naive_Integer aPU, aPV, aWU, aWV;
  if (math::Util::List2CheckBound(thePoles, aPU, aPV) ||
      math::Util::List2CheckBound(theWeights, aWU, aWV))
    return Naive_Code_invalid_value;

  if (aPU < 2 || aPV < 2)
    return Naive_Code_value_out_of_range;

  if (aPU != aWU || aPV != aWV)
    return Naive_Code_poles_weights_not_match;

  Naive_XYZWList2 aCPs(aPU, Naive_XYZWList1(aPV));

  for (Naive_Integer u = 0; u < aPU; ++u) {
    for (Naive_Integer v = 0; v < aPV; ++v) {
      aCPs[u][v] = thePoles[u][v].HomoCoord() * theWeights[u][v];
    }
  }

  return update(::std::move(aCPs), theUKnots, theVKnots, theUMults, theVMults,
                theUDegree, theVDegree, theUPeriodic, theVPeriodic);
}

Naive_Code NurbsSurface::Init(const Naive_NurbsSurface_sf_t &theSF) noexcept {
  int u_degree = theSF.u_degree;
  int v_degree = theSF.v_degree;
  int n_u_vertices = theSF.n_u_vertices;
  int n_v_vertices = theSF.n_v_vertices;
  int vertex_dim = theSF.vertex_dim;
  double *vertex = theSF.vertex;
  int n_u_knots = theSF.n_u_knots;
  int n_v_knots = theSF.n_v_knots;
  int *u_knot_mult = theSF.u_knot_mult;
  int *v_knot_mult = theSF.v_knot_mult;
  double *u_knot = theSF.u_knot;
  double *v_knot = theSF.v_knot;

  if (!vertex || !u_knot_mult || !v_knot_mult || !u_knot || !v_knot)
    return Naive_Code_invalid_value;

  if (n_u_vertices < 2 || n_v_vertices < 2)
    return Naive_Code_insufficient_points;

  if (n_u_knots < 2 || n_v_knots < 2)
    return Naive_Code_insufficient_knots;

  if (u_degree < 1 || v_degree < 1)
    return Naive_Code_value_out_of_range;

  Naive_XYZWList2 aCPs(n_u_vertices, Naive_XYZWList1(n_v_vertices));

  if (theSF.is_rational && vertex_dim == 4) {
    for (Naive_XYZWList1 &aVP : aCPs) {
      for (Naive_XYZW &aCP : aVP) {
        aCP.x() = *(vertex++);
        aCP.y() = *(vertex++);
        aCP.z() = *(vertex++);
        aCP.w() = *(vertex++);
      }
    }
  } else if (!theSF.is_rational && vertex_dim == 3) {
    for (Naive_XYZWList1 &aVP : aCPs) {
      for (Naive_XYZW &aCP : aVP) {
        aCP.x() = *(vertex++);
        aCP.y() = *(vertex++);
        aCP.z() = *(vertex++);
        aCP.w() = 1.;
      }
    }
  } else {
    return Naive_Code_bad_dimension;
  }

  Naive_RealList1 aUKnots(u_knot, u_knot + n_u_knots);
  Naive_RealList1 aVKnots(v_knot, v_knot + n_v_knots);
  Naive_IntegerList1 aUMults(u_knot_mult, u_knot_mult + n_u_knots);
  Naive_IntegerList1 aVMults(v_knot_mult, v_knot_mult + n_v_knots);

  return update(::std::move(aCPs), ::std::move(aUKnots), ::std::move(aVKnots),
                ::std::move(aUMults), ::std::move(aVMults), u_degree, v_degree,
                theSF.is_u_periodic, theSF.is_v_periodic);
}

Naive_Bool NurbsSurface::IsValid() const {
  return myUDegree > 0 && myVDegree > 0;
}

Handle_Naive_Geometry NurbsSurface::Clone() const {
  return new NurbsSurface(*this);
}

Naive_Bool NurbsSurface::Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                Naive_Real &theV0, Naive_Real &theV1) const {
  if (!IsValid())
    return Naive_False;

  theU0 = myUKnots[0];
  theU1 = myUKnots[myUKnots.size() - 1];
  theV0 = myVKnots[0];
  theV1 = myVKnots[myVKnots.size() - 1];

  return Naive_True;
}

Naive_Pnt3d Surface::PointAt(const Naive_Real theU,
                             const Naive_Real theV) const {
  Naive_Vec3dList2 aD{};
  if (Evaluate(theU, theV, 0, aD) != Naive_Code_ok)
    return Naive_Pnt3d::Unset();
  return aD[0][0].XYZ();
}

Naive_Code NurbsSurface::Evaluate(const Naive_Real theU, const Naive_Real theV,
                                  const Naive_Integer theN,
                                  Naive_Vec3dList2 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  return math::Nurbs::SurfaceEvaluate(
      myCPs, myUFlatKnots, myVFlatKnots, myUKnots, myVKnots, myUMults, myVMults,
      myUDegree, myVDegree, theU, theV, theN, theD);
}

Naive_Bool NurbsSurface::IsUClosed() const { return Naive_False; }

Naive_Bool NurbsSurface::IsVClosed() const { return Naive_False; }

Naive_Bool NurbsSurface::IsUPeriodic() const { return myUPeriodic; }

Naive_Bool NurbsSurface::IsVPeriodic() const { return myVPeriodic; }

Naive_Real NurbsSurface::UPeriod() const { return math::Constant::UnsetReal(); }

Naive_Real NurbsSurface::VPeriod() const { return math::Constant::UnsetReal(); }

Naive_Code NurbsSurface::Dump(Naive_NurbsSurface_sf_t &theSF,
                              const common::MemHandler &theHandler) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  theSF.u_degree = UDegree();
  theSF.v_degree = VDegree();
  theSF.is_rational = IsURational() || IsVRational();
  theSF.vertex_dim = theSF.is_rational ? 4 : 3;
  theSF.form = Naive_NurbsSurface_form_unset_c;
  theSF.is_u_periodic = IsUPeriodic();
  theSF.is_v_periodic = IsVPeriodic();
  theSF.is_u_closed = IsUClosed();
  theSF.is_v_closed = IsVClosed();
  theSF.vertex = nullptr;
  theSF.u_knot_mult = nullptr;
  theSF.v_knot_mult = nullptr;
  theSF.u_knot = nullptr;
  theSF.v_knot = nullptr;

  Naive_Code aCode;

  /* TODO: Arrays. */

  return Naive_Code_not_implemented;

CLEAN:
  theHandler.Deleter(theSF.vertex);
  theHandler.Deleter(theSF.u_knot_mult);
  theHandler.Deleter(theSF.v_knot_mult);
  theHandler.Deleter(theSF.u_knot);
  theHandler.Deleter(theSF.v_knot);
  theSF.vertex = nullptr;
  theSF.u_knot_mult = nullptr;
  theSF.v_knot_mult = nullptr;
  theSF.u_knot = nullptr;
  theSF.v_knot = nullptr;
  return aCode;
}

Naive_Code NurbsSurface::transform(const Naive_Trsf3d &theTrsf) {
  return Naive_Code_not_implemented;
}

Naive_NAMESPACE_END(geometry);
