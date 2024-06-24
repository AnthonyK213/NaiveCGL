#include <naivecgl/BndShape/ConvexHull2D.h>
#include <naivecgl/BndShape/ConvexHull3D.h>
#include <naivecgl/BndShape/EnclosingDisc.h>
#include <naivecgl/Geometry/Line.h>
#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Geometry/Plane.h>
#include <naivecgl/Interface/NaiveCGL_c.h>
#include <naivecgl/Intersect/Intersection.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Tessellation/Sphere.h>
#include <naivecgl/Topology/Body.h>

#define Naive_H_CAST(T, H, N) T *N = reinterpret_cast<T *>(H);
#define Naive_H_CAST_AND_CHECK(T, H, N)                                        \
  Naive_H_CAST(T, H, N);                                                       \
  if (!N) {                                                                    \
    return Naive_Code_invalid_handle;                                          \
  }

/// Naive_Math_Util {{{

Naive_Code_t Naive_Math_Util_is_valid_real(const double real,
                                           Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_Code_null_arg_address;

  *is_valid = ::naivecgl::math::Util::IsValidReal(real);
  return Naive_Code_ok;
}

/// }}}

/// Naive_Object {{{

Naive_Code_t Naive_Object_free(Naive_Object_t Object) {
  Naive_H_CAST(Naive_Object, Object, H);
  if (H && H->DecrementRefCounter() == 0)
    H->Delete();
  return Naive_Code_ok;
}

/// }}}

/// Naive_Geometry {{{

Naive_Code_t Naive_Geometry_is_valid(const Naive_Geometry_t geometry,
                                     Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Geometry, geometry, H);
  *is_valid = H->IsValid();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Geometry_clone(const Naive_Geometry_t geometry,
                                  Naive_Geometry_t *const clone) {
  if (!clone)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Geometry, geometry, H);
  Handle_Naive_Geometry aClone = H->Clone();
  aClone->IncrementRefCounter();
  *clone = aClone.get();
  return Naive_Code_ok;
}

/// }}}

/// Naive_Curve {{{

Naive_Code_t Naive_Curve_ask_bound(const Naive_Curve_t curve,
                                   Naive_Interval_t *const bound) {
  if (!bound)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Curve, curve, H);
  if (!H->IsValid())
    return Naive_Code_invalid_handle;
  bound->t0 = H->FirstParameter();
  bound->t1 = H->LastParameter();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Curve_evaluate(const Naive_Curve_t curve, const double t,
                                  const int n_derivative, int *const n_result,
                                  Naive_Vector3d_t *const result) {
  if (!n_result)
    return Naive_Code_null_arg_address;

  if (n_derivative < 0)
    return Naive_Code_value_out_of_range;

  *n_result = n_derivative + 1;

  if (result) {
    Naive_H_CAST_AND_CHECK(const Naive_Curve, curve, H);
    Naive_Vec3dList1 aD{};
    Naive_Code aCode = H->DerivativeAt(t, n_derivative, aD);
    if (aCode)
      return aCode;

    for (Naive_Integer i = 0; i < *n_result; ++i) {
      aD[i].Dump(result[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Curve_curvature_at(const Naive_Curve_t curve, const double t,
                                      Naive_Vector3d_t *const curvature) {
  if (!curvature)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Curve, curve, H);
  Naive_Vec3d aCurvature;
  Naive_Code aCode = H->CurvatureAt(t, aCurvature);
  if (aCode)
    return aCode;
  aCurvature.Dump(*curvature);
  return Naive_Code_ok;
}

///}}}

/// Naive_Surface {{{

Naive_Code_t Naive_Surface_evaluate(const Naive_Surface_t surface,
                                    const double u, const double v,
                                    const int n_derivative, int *const n_result,
                                    Naive_Vector3d_t *const result) {
  if (!n_result)
    return Naive_Code_null_arg_address;

  if (n_derivative < 0)
    return Naive_Code_invalid_value;

  *n_result = (n_derivative + 1) * (n_derivative + 2) >> 1;

  if (result) {
    Naive_H_CAST_AND_CHECK(const Naive_Surface, surface, H);
    Naive_Vec3dList1 aD{};
    Naive_Code aCode = H->Evaluate(u, v, n_derivative, aD);
    if (aCode)
      return aCode;

    for (Naive_Integer i = 0; i < *n_result; ++i) {
      aD[i].Dump(result[i]);
    }
  }

  return Naive_Code_ok;
}

/// }}}

/// Naive_Plane {{{

Naive_Code_t Naive_Plane_new(const Naive_Plane_sf_t *plane_sf,
                             Naive_Plane_t *const plane) {
  if (!plane_sf || !plane)
    return Naive_Code_null_arg_address;

  Handle_Naive_Plane aPlane = new Naive_Plane(*plane_sf);
  aPlane->IncrementRefCounter();
  *plane = aPlane.get();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Plane_ask(const Naive_Plane_t plane,
                             Naive_Plane_sf_t *const plane_sf) {
  if (!plane_sf)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Plane, plane, H);
  return (H->Pln().Dump(*plane_sf)) ? Naive_Code_ok : Naive_Code_invalid_handle;
}

Naive_Code_t Naive_Plane_distance(const Naive_Plane_t plane,
                                  const Naive_Point3d_t *point,
                                  double *const distance) {
  if (!point)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Plane, plane, H);
  double aDistance = H->Distance(*point);
  if (!::naivecgl::math::Util::IsValidReal(aDistance))
    return Naive_Code_invalid_value;
  *distance = aDistance;
  return Naive_Code_ok;
}

/// }}}

/// Naive_Line {{{

Naive_Code_t Naive_Line_new(const Naive_Line_sf_t *line_sf,
                            Naive_Line_t *const line) {
  if (!line_sf || !line)
    return Naive_Code_null_arg_address;

  Handle_Naive_Line aLine = new Naive_Line(*line_sf);
  aLine->IncrementRefCounter();
  *line = aLine.get();
  return Naive_Code_ok;
}

/// }}}

/// Naive_NurbsCurve {{{

Naive_Code_t Naive_NurbsCurve_new(const int n_poles,
                                  const Naive_Point3d_t *poles,
                                  const int n_weights, const double *weights,
                                  const int n_knots, const double *knots,
                                  const int n_mults, const int *mults,
                                  const int degree,
                                  Naive_NurbsCurve_t *const nurbs_curve) {
  if (!poles || !weights || !knots || !mults || !nurbs_curve)
    return Naive_Code_null_arg_address;

  if (n_poles < 2 || n_weights < 2 || n_knots < 2 || n_mults < 2 || degree < 1)
    return Naive_Code_value_out_of_range;

  Naive_Pnt3dList1 aPoles(poles, poles + n_poles);
  Naive_RealList1 aWeights(weights, weights + n_weights);
  Naive_RealList1 aKnots(knots, knots + n_knots);
  Naive_IntegerList1 aMults(mults, mults + n_mults);

  Handle_Naive_NurbsCurve aCrv = new Naive_NurbsCurve;
  Naive_Code aCode = aCrv->Init(aPoles, aWeights, aKnots, aMults, degree);
  if (aCode)
    return aCode;

  aCrv->IncrementRefCounter();
  *nurbs_curve = aCrv.get();
  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_degree(const Naive_NurbsCurve_t nurbs_curve,
                                         int *const degree) {
  if (!degree)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  *degree = H->Degree();
  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_poles(const Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_poles,
                                        Naive_Point3d_t *const poles) {
  if (!n_poles)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbPoles = H->NbPoles();
  if (nbPoles <= 0)
    return Naive_Code_invalid_handle;

  *n_poles = nbPoles;

  if (poles) {
    const Naive_Pnt3dList1 &aPoles = H->Poles();
    for (Naive_Integer i = 0; i < nbPoles; ++i) {
      aPoles[i].Dump(poles[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_weights(const Naive_NurbsCurve_t nurbs_curve,
                                          int *const n_weights,
                                          double *const weights) {
  if (!n_weights)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbWeights = H->NbPoles();
  if (nbWeights <= 0)
    return Naive_Code_invalid_handle;

  *n_weights = nbWeights;

  if (weights) {
    const Naive_RealList1 &aWeights = H->Weights();
    ::std::copy(aWeights.cbegin(), aWeights.cend(), weights);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_knots(const Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_knots,
                                        double *const knots) {
  if (!n_knots)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbKnots = H->NbKnots();
  if (nbKnots <= 0)
    return Naive_Code_invalid_handle;

  *n_knots = nbKnots;

  if (knots) {
    const Naive_RealList1 &aKnots = H->Knots();
    ::std::copy(aKnots.cbegin(), aKnots.cend(), knots);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_mults(const Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_mults, int *const mults) {
  if (!n_mults)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbMults = H->NbKnots();
  if (nbMults <= 0)
    return Naive_Code_invalid_handle;

  *n_mults = nbMults;

  if (mults) {
    const Naive_IntegerList1 &aMults = H->Multiplicities();
    ::std::copy(aMults.cbegin(), aMults.cend(), mults);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_increase_degree(Naive_NurbsCurve_t nurbs_curve,
                                              const int degree) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->IncreaseDegree(degree);
}

Naive_Code_t
Naive_NurbsCurve_increase_multiplicity(Naive_NurbsCurve_t nurbs_curve,
                                       const int index, const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->IncreaseMultiplicity(index, mult);
}

Naive_Code_t Naive_NurbsCurve_insert_knot(Naive_NurbsCurve_t nurbs_curve,
                                          const double t, const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->InsertKnot(t, mult);
}

Naive_Code_t Naive_NurbsCurve_remove_knot(Naive_NurbsCurve_t nurbs_curve,
                                          const int index, const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->RemoveKnot(index, mult);
}

/// }}}

/// Naive_NurbsSurface {{{

Naive_Code_t Naive_NurbsSurface_new(
    const int n_poles_u, const int n_poles_v, const Naive_Point3d_t *poles,
    const int n_weights_u, const int n_weights_v, const double *weights,
    const int n_knots_u, const double *knots_u, const int n_knots_v,
    const double *knots_v, const int n_mults_u, const int *mults_u,
    const int n_mults_v, const int *mults_v, const int degree_u,
    const int degree_v, Naive_NurbsSurface_t *const nurbs_surface) {
  if (!poles || !weights || !knots_u || !knots_v || !mults_u || !mults_v ||
      !nurbs_surface)
    return Naive_Code_null_arg_address;

  if (n_poles_u < 2 || n_poles_v < 2 || n_weights_u < 2 || n_weights_v < 2 ||
      n_knots_u < 2 || n_knots_v < 2 || n_mults_u < 2 || n_mults_v < 2 ||
      degree_u < 1 || degree_v < 1)
    return Naive_Code_value_out_of_range;

  Naive_Pnt3dList2 aPoles{};
  aPoles.reserve(n_poles_u);
  const Naive_Point3d_t *aPHead = poles;
  for (Naive_Integer i = 0; i < n_poles_u; ++i, aPHead += n_poles_v) {
    Naive_Pnt3dList1 aVP(aPHead, aPHead + n_poles_v);
    aPoles.emplace_back(::std::move(aVP));
  }
  Naive_RealList2 aWeights{};
  aWeights.reserve(n_weights_u);
  const Naive_Real *aWHead = weights;
  for (Naive_Integer i = 0; i < n_weights_u; ++i, aWHead += n_weights_v) {
    Naive_RealList1 aVW(aWHead, aWHead + n_weights_v);
    aWeights.emplace_back(::std::move(aVW));
  }
  Naive_RealList1 aUKnots(knots_u, knots_u + n_knots_u);
  Naive_RealList1 aVKnots(knots_v, knots_v + n_knots_v);
  Naive_IntegerList1 aUMults(mults_u, mults_u + n_mults_u);
  Naive_IntegerList1 aVMults(mults_v, mults_v + n_mults_v);

  Handle_Naive_NurbsSurface aSrf = new Naive_NurbsSurface;
  Naive_Code aCode = aSrf->Init(aPoles, aWeights, aUKnots, aVKnots, aUMults,
                                aVMults, degree_u, degree_v);
  if (aCode)
    return aCode;

  aSrf->IncrementRefCounter();
  *nurbs_surface = aSrf.get();
  return Naive_Code_ok;
}

Naive_Code_t
Naive_NurbsSurface_ask_degree(const Naive_NurbsSurface_t nurbs_surface,
                              int *const degree_u, int *const degree_v) {
  Naive_H_CAST_AND_CHECK(const Naive_NurbsSurface, nurbs_surface, H);
  if (degree_u)
    *degree_u = H->UDegree();
  if (degree_v)
    *degree_v = H->VDegree();
  return Naive_Code_ok;
}

/// }}}

/// Naive_Poly {{{

Naive_Code_t Naive_Poly_new(const int n_vertices,
                            const Naive_Point3d_t *vertices,
                            const int n_triangles,
                            const Naive_Triangle_t *triangles,
                            Naive_Poly_t *const poly) {
  if (!vertices || !triangles || !poly)
    return Naive_Code_null_arg_address;

  if (n_vertices < 0 || n_triangles < 0)
    return Naive_Code_err;

  Naive_Pnt3dList1 aVerts(n_vertices);
  for (int i = 0; i < n_vertices; ++i) {
    aVerts[i] = vertices[i];
  }

  Naive_List1<Naive_Triangle> aTris(n_triangles);
  for (int i = 0; i < n_triangles; ++i) {
    aTris[i].x() = triangles[i].n0;
    aTris[i].y() = triangles[i].n1;
    aTris[i].z() = triangles[i].n2;
  }

  Handle_Naive_Poly aPoly =
      new Naive_Poly(::std::move(aVerts), ::std::move(aTris));
  aPoly->IncrementRefCounter();
  *poly = aPoly.get();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_is_valid(const Naive_Poly_t poly,
                                 Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Poly, poly, H);
  *is_valid = H->IsValid();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_clone(const Naive_Poly_t poly,
                              Naive_Poly_t *const clone) {
  if (!clone)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Poly, poly, H);
  Handle_Naive_Poly aClone = new Naive_Poly(*H);
  aClone->IncrementRefCounter();
  *clone = aClone.get();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_ask_vertices(const Naive_Poly_t poly,
                                     int *const n_vertices,
                                     Naive_Point3d_t *const vertices) {
  if (!n_vertices)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Poly, poly, H);
  int nbVerts = static_cast<int>(H->Vertices().size());
  *n_vertices = nbVerts;

  if (vertices) {
    for (Naive_Size i = 0; i < nbVerts; ++i) {
      H->Vertices()[i].Dump(vertices[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Poly_ask_triangles(const Naive_Poly_t poly,
                                      int *const n_triangles,
                                      Naive_Triangle_t *const triangles) {
  if (!n_triangles)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Poly, poly, H);
  int nbTris = static_cast<int>(H->Triangles().size());
  *n_triangles = nbTris;

  if (triangles) {
    for (Naive_Size i = 0; i < nbTris; ++i) {
      const Naive_Triangle &aTriangle = H->Triangles()[i];
      triangles[i].n0 = aTriangle(0);
      triangles[i].n1 = aTriangle(1);
      triangles[i].n2 = aTriangle(2);
    }
  }

  return Naive_Code_ok;
}

/// }}}

/// Naive_BndShape_ConvexHull2D {{{

Naive_Code_t
Naive_BndShape_ConvexHull2D_new(int n_points, const Naive_Point2d_t *points,
                                Naive_Algorithm_t algo,
                                Naive_ConvexHull2D_t *const convex_hull_2d) {
  if (!points || !convex_hull_2d)
    return Naive_Code_null_arg_address;

  if (n_points < 0)
    return Naive_Code_err;

  Naive_Pnt2dList1 aPoints(n_points);
  for (Naive_Integer i = 0; i < n_points; ++i) {
    aPoints[i] = points[i];
  }

  Naive_Handle<::naivecgl::bndshape::ConvexHull2D> aCH2D =
      new ::naivecgl::bndshape::ConvexHull2D(
          ::std::move(aPoints), static_cast<Naive_Algorithm>(algo));
  aCH2D->IncrementRefCounter();
  *convex_hull_2d = aCH2D.get();
  return Naive_Code_ok;
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_set_algorithm(Naive_ConvexHull2D_t convex_hull_2d,
                                          Naive_Algorithm_t algo) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, convex_hull_2d, H);
  H->SetAlgorithm(static_cast<Naive_Algorithm>(algo));
  return H->Status();
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_perform(Naive_ConvexHull2D_t convex_hull_2d) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, convex_hull_2d, H);
  H->Perform();
  return H->Status();
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_add_point(Naive_ConvexHull2D_t convex_hull_2d,
                                      Naive_Point2d_t point,
                                      Naive_Logical_t to_perform) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, convex_hull_2d, H);
  H->Add(point, to_perform);
  return H->Status();
}

Naive_Code_t Naive_BndShape_ConvexHull2D_ask_result(
    const Naive_ConvexHull2D_t convex_hull_2d, int *const n_convex_points,
    int *const convex_indices, Naive_Point2d_t *const convex_points) {
  if (!n_convex_points)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const ::naivecgl::bndshape::ConvexHull2D,
                         convex_hull_2d, H);
  if (H->Status() != Naive_Code_ok)
    return H->Status();

  *n_convex_points = H->NbConvexPoints();

  if (convex_indices) {
    Naive_IntegerList1 anIndices = H->ConvexIndices();
    ::std::copy(anIndices.cbegin(), anIndices.cend(), convex_indices);
  }

  if (convex_points) {
    Naive_Pnt2dList1 aPoints = H->ConvexPoints();
    for (Naive_Integer i = 0; i < aPoints.size(); ++i) {
      aPoints[i].Dump(convex_points[i]);
    }
  }

  return Naive_Code_ok;
}

/// }}}

/// Naive_BndShape_EnclosingDisc {{{

Naive_Code_t
Naive_BndShape_EnclosingDisc_new(Naive_EnclosingDisc_t *const enclosing_disc) {
  if (!enclosing_disc)
    return Naive_Code_null_arg_address;

  Naive_Handle<::naivecgl::bndshape::EnclosingDisc> aED =
      new ::naivecgl::bndshape::EnclosingDisc();
  aED->IncrementRefCounter();
  *enclosing_disc = aED.get();
  return Naive_Code_ok;
}

Naive_Code_t
Naive_BndShape_EnclosingDisc_rebuild(Naive_EnclosingDisc_t enclosing_disc,
                                     const int n_points,
                                     const Naive_Point2d_t *points) {
  if (!points)
    return Naive_Code_null_arg_address;

  if (n_points < 0)
    return Naive_Code_invalid_value;

  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::EnclosingDisc, enclosing_disc,
                         H);
  Naive_Pnt2dList1 aPoints(points, points + n_points);
  H->ReBuild(aPoints);
  return Naive_Code_ok;
}

Naive_Code_t Naive_BndShape_EnclosingDisc_ask_circle(
    const Naive_EnclosingDisc_t enclosing_disc,
    Naive_Point2d_t *const theOrigin, double *const theR) {
  if (!theOrigin || !theR)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const ::naivecgl::bndshape::EnclosingDisc,
                         enclosing_disc, H);
  Naive_Pnt2d anOrigin;
  Naive_Real aR;
  if (!H->Circle(anOrigin, aR))
    return Naive_Code_err;

  anOrigin.Dump(*theOrigin);
  *theR = aR;
  return Naive_Code_ok;
}

/// }}}

/// Naive_Intersect_Intersection {{{

Naive_Code_t Naive_Intersect_Intersection_line_plane(const Naive_Line_t line,
                                                     const Naive_Plane_t plane,
                                                     double *const t) {
  if (!t)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Line, line, HL);
  Naive_H_CAST_AND_CHECK(const Naive_Pln, plane, HP);
  Handle_Naive_Line aLine = new Naive_Line(*HL);
  Handle_Naive_Plane aPlane = new Naive_Plane(*HP);
  return ::naivecgl::intersect::Intersection::LinePlane(aLine, aPlane, *t);
}

/// }}}

/// Naive_Tessellation {{{

Naive_Code_t Naive_Tessellation_tetrasphere(const Naive_Point3d_t *center,
                                            double radius, int level,
                                            Naive_Poly_t *const poly) {
  if (!center || !poly)
    return Naive_Code_null_arg_address;

  if (radius <= ::naivecgl::math::Constant::ZeroTolerance() || level < 0)
    return Naive_Code_value_out_of_range;

  Naive_Pnt3d aCenter{*center};
  Handle_Naive_Poly aPoly =
      ::naivecgl::tessellation::TetraSphere(aCenter, radius, level);
  if (!aPoly)
    return Naive_Code_err;

  aPoly->IncrementRefCounter();
  *poly = aPoly.get();
  return Naive_Code_ok;
}

/// }}}

/// Naive_Body {{{

Naive_Code_t Naive_Body_ask_location(const Naive_Body_t body,
                                     Naive_Transform3d_t *const location) {
  return Naive_Code_not_implemented;
}

Naive_Code_t
Naive_Body_ask_orientation(const Naive_Body_t body,
                           Naive_Orientation_t *const orientation) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_edges(const Naive_Body_t body, int *const n_edges,
                                  Naive_Edge_t *const edges) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_faces(const Naive_Body_t body, int *const n_faces,
                                  Naive_Face_t *const faces) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_fins(const Naive_Body_t body, int *const n_fins,
                                 Naive_Fin_t *const fins) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_loops(const Naive_Body_t body, int *const n_loops,
                                  Naive_Loop_t *const loops) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_shells(const Naive_Body_t body, int *const n_shells,
                                   Naive_Shell_t *const shells) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_ask_vertices(const Naive_Body_t body,
                                     int *const n_vertices,
                                     Naive_Vertex_t *const vertices) {
  return Naive_Code_not_implemented;
}

Naive_Code_t Naive_Body_boolean(const Naive_Body_t target, const int n_tools,
                                const Naive_Body_t *tools,
                                const Naive_Body_boolean_o_t *options) {
  return Naive_Code_not_implemented;
}

/// }}}

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
