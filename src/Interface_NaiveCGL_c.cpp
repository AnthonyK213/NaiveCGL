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

#define Naive_H_CAST(T, H, N) T *N = reinterpret_cast<T *>(H);
#define Naive_H_CAST_AND_CHECK(T, H, N)                                        \
  Naive_H_CAST(T, H, N);                                                       \
  if (!N) {                                                                    \
    return Naive_InvalidHandle;                                                \
  }

/// Math_Constant {{{

double Naive_Math_Constant_PI(void) { return ::naivecgl::math::Constant::PI(); }

double Naive_Math_Constant_Epsilon(void) {
  return ::naivecgl::math::Constant::Epsilon();
}

double Naive_Math_Constant_MinReal(void) {
  return ::naivecgl::math::Constant::MinReal();
}

double Naive_Math_Constant_MaxReal(void) {
  return ::naivecgl::math::Constant::MaxReal();
}

double Naive_Math_Constant_UnsetReal(void) {
  return ::naivecgl::math::Constant::UnsetReal();
}

// }}}

/// Math_Util {{{

Naive_Logical_t Naive_Math_Util_IsValidReal(const double real) {
  return ::naivecgl::math::Util::IsValidReal(real);
}

/// }}}

/// Naive_Transient {{{

Naive_Code_t Naive_Transient_Release(Naive_Handle_t hd) {
  Naive_H_CAST(Naive_Transient, hd, H);
  if (H && H->DecrementRefCounter() == 0)
    H->Delete();
  return Naive_Ok;
}

/// }}}

/// Naive_Geometry {{{

Naive_Code_t Naive_Geometry_IsValid(const Naive_Handle_t hd,
                                    Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Geometry, hd, H);
  *is_valid = H->IsValid();
  return Naive_Ok;
}

Naive_Code_t Naive_Geometry_Clone(const Naive_Handle_t hd,
                                  Naive_Handle_t *const clone) {
  if (!clone)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Geometry, hd, H);
  Handle_Naive_Geometry aClone = H->Clone();
  aClone->IncrementRefCounter();
  *clone = aClone.get();
  return Naive_Ok;
}

/// }}}

/// Naive_Plane {{{

Naive_Code_t Naive_Plane_New(const Naive_Plane_t *plane_sf,
                             Naive_Handle_t *const plane) {
  if (!plane_sf || !plane)
    return Naive_NullException;

  Handle_Naive_Plane aPlane = new Naive_Plane(*plane_sf);
  aPlane->IncrementRefCounter();
  *plane = aPlane.get();
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_Location(const Naive_Handle_t hd,
                                  Naive_Point3d_t *const location) {
  if (!location)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Plane, hd, H);
  if (!H->Location().Dump(*location))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_XAxis(const Naive_Handle_t hd,
                               Naive_Point3d_t *const x_axis) {
  if (!x_axis)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Plane, hd, H);
  if (!H->XAxis().Dump(*x_axis))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_YAxis(const Naive_Handle_t hd,
                               Naive_Point3d_t *const y_axis) {
  if (!y_axis)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Plane, hd, H);
  if (!H->YAxis().Dump(*y_axis))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_Axis(const Naive_Handle_t hd,
                              Naive_Point3d_t *const axis) {
  if (!axis)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Plane, hd, H);
  if (!H->Axis().Dump(*axis))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_Plane_Distance(const Naive_Handle_t hd,
                                  const Naive_Point3d_t *point,
                                  double *const distance) {
  if (!point)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Plane, hd, H);
  double aDistance = H->Distance(*point);
  if (!::naivecgl::math::Util::IsValidReal(aDistance))
    return Naive_InvalidValue;
  *distance = aDistance;
  return Naive_Ok;
}

/// }}}

/// Naive_Line {{{

Naive_Code_t Naive_Line_New(const Naive_Line_t *line_sf,
                            Naive_Handle_t *const line) {
  if (!line_sf || !line)
    return Naive_NullException;

  Handle_Naive_Line aLine = new Naive_Line(*line_sf);
  aLine->IncrementRefCounter();
  *line = aLine.get();
  return Naive_Ok;
}

/// }}}

/// Naive_NurbsCurve {{{

Naive_Code_t Naive_NurbsCurve_New(const int n_poles,
                                  const Naive_Point3d_t *poles,
                                  const int n_weights, const double *weights,
                                  const int n_knots, const double *knots,
                                  const int n_mults, const int *mults,
                                  const int degree,
                                  Naive_Handle_t *const nurbs_curve) {
  if (!poles || !weights || !knots || !mults || !nurbs_curve)
    return Naive_NullException;

  if (n_poles < 2 || n_weights < 2 || n_knots < 2 || n_mults < 2 || degree < 1)
    return Naive_Err;

  Naive_Point3dList aPoles(poles, poles + n_poles);
  Naive_RealList aWeights(weights, weights + n_weights);
  Naive_RealList aKnots(knots, knots + n_knots);
  Naive_IntegerList aMults(mults, mults + n_mults);
  Handle_Naive_NurbsCurve aCrv =
      new Naive_NurbsCurve(aPoles, aWeights, aKnots, aMults, degree);
  aCrv->IncrementRefCounter();
  *nurbs_curve = aCrv.get();
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_Degree(const Naive_Handle_t hd,
                                     int *const degree) {
  if (!degree)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  *degree = H->Degree();
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_NbPoles(const Naive_Handle_t hd,
                                      int *const n_poles) {
  if (!n_poles)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  Naive_Integer nbPoles = H->NbPoles();
  if (nbPoles <= 0)
    return Naive_InvalidValue;
  *n_poles = nbPoles;
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_Pole(const Naive_Handle_t hd, const int index,
                                   Naive_Point3d_t *const pole) {
  if (!pole)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  if (!H->Pole(index).Dump(*pole))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_Weight(const Naive_Handle_t hd, const int index,
                                     double *const weight) {
  if (!weight)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  Naive_Real aWeight = H->Weight(index);
  if (!::naivecgl::math::Util::IsValidReal(aWeight))
    return Naive_InvalidValue;
  *weight = aWeight;
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_NbKnots(const Naive_Handle_t hd,
                                      int *const n_knots) {
  if (!n_knots)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  Naive_Integer nbKnots = H->NbKnots();
  if (nbKnots <= 0)
    return Naive_InvalidValue;
  *n_knots = nbKnots;
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_Knot(const Naive_Handle_t hd, const int index,
                                   double *const knot) {
  if (!knot)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  Naive_Real aKnot = H->Knot(index);
  if (!::naivecgl::math::Util::IsValidReal(aKnot))
    return Naive_InvalidValue;
  *knot = aKnot;
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_Multiplicity(const Naive_Handle_t hd,
                                           const int index, int *const mult) {
  if (!mult)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  Naive_Integer aMult = H->Multiplicity(index);
  if (aMult <= 0)
    return Naive_InvalidValue;
  *mult = aMult;
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_Bound(const Naive_Handle_t hd,
                                    Naive_Interval_t *const bound) {
  if (!bound)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
  if (!H->IsValid())
    return Naive_InvalidValue;
  bound->t0 = H->FirstParameter();
  bound->t1 = H->LastParameter();
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_Evaluate(const Naive_Handle_t hd, const double t,
                                       const int n_derivative,
                                       int *const n_result,
                                       Naive_Vector3d_t *const result) {
  if (!n_result)
    return Naive_NullException;

  if (n_derivative < 0)
    return Naive_InvalidValue;

  *n_result = n_derivative + 1;

  if (result) {
    Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, hd, H);
    Naive_Vector3dList aD{};
    if (!H->DerivativeAt(t, n_derivative, aD))
      return Naive_InvalidValue;

    for (Naive_Integer i = 0; i < *n_result; ++i) {
      aD[i].Dump(result[i]);
    }
  }

  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_CurvatureAt(const Naive_Handle_t hd,
                                          const double t,
                                          Naive_Vector3d_t *const curvature) {
  if (!curvature)
    return Naive_NullException;

  Naive_H_CAST(const Naive_NurbsCurve, hd, H);
  if (!H->CurvatureAt(t).Dump(*curvature))
    return Naive_InvalidValue;
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsCurve_IncreaseDegree(Naive_Handle_t hd,
                                             const int degree) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, hd, H);
  return (H->IncreaseDegree(degree)) ? Naive_Ok : Naive_Err;
}

Naive_Code_t Naive_NurbsCurve_IncreaseMultiplicity(Naive_Handle_t hd,
                                                   const int index,
                                                   const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, hd, H);
  return (H->IncreaseMultiplicity(index, mult)) ? Naive_Ok : Naive_Err;
}

Naive_Code_t Naive_NurbsCurve_InsertKnot(Naive_Handle_t hd, const double t,
                                         const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, hd, H);
  return (H->InsertKnot(t, mult)) ? Naive_Ok : Naive_Err;
}

Naive_Code_t Naive_NurbsCurve_RemoveKnot(Naive_Handle_t hd, const int index,
                                         const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, hd, H);
  return (H->RemoveKnot(index, mult)) ? Naive_Ok : Naive_Err;
}

/// }}}

/// Naive_NurbsSurface {{{

Naive_Code_t Naive_NurbsSurface_New(
    const int n_poles_u, const int n_poles_v, const Naive_Point3d_t *poles,
    const int n_weights_u, const int n_weights_v, const double *weights,
    const int n_knots_u, const double *knots_u, const int n_knots_v,
    const double *knots_v, const int n_mults_u, const int *mults_u,
    const int n_mults_v, const int *mults_v, const int degree_u,
    const int degree_v, Naive_Handle_t *const nurbs_surface) {
  if (!poles || !weights || !knots_u || !knots_v || !mults_u || !mults_v ||
      !nurbs_surface)
    return Naive_NullException;

  if (n_poles_u < 2 || n_poles_v < 2 || n_weights_u < 2 || n_weights_v < 2 ||
      n_knots_u < 2 || n_knots_v < 2 || n_mults_u < 2 || n_mults_v < 2 ||
      degree_u < 1 || degree_v < 1)
    return Naive_InvalidValue;

  Naive_Point3dList2 aPoles{};
  aPoles.reserve(n_poles_u);
  const Naive_Point3d_t *aPHead = poles;
  for (Naive_Integer i = 0; i < n_poles_u; ++i, aPHead += n_poles_v) {
    Naive_Point3dList aVP(aPHead, aPHead + n_poles_v);
    aPoles.push_back(::std::move(aVP));
  }
  Naive_RealList2 aWeights{};
  aWeights.reserve(n_weights_u);
  const Naive_Real *aWHead = weights;
  for (Naive_Integer i = 0; i < n_weights_u; ++i, aWHead += n_weights_v) {
    Naive_RealList aVW(aWHead, aWHead + n_weights_v);
    aWeights.push_back(::std::move(aVW));
  }
  Naive_RealList aUKnots(knots_u, knots_u + n_knots_u);
  Naive_RealList aVKnots(knots_v, knots_v + n_knots_v);
  Naive_IntegerList aUMults(mults_u, mults_u + n_mults_u);
  Naive_IntegerList aVMults(mults_v, mults_v + n_mults_v);
  Handle_Naive_NurbsSurface aSrf = new Naive_NurbsSurface(
      aPoles, aWeights, aUKnots, aVKnots, aUMults, aVMults, degree_u, degree_v);
  aSrf->IncrementRefCounter();
  *nurbs_surface = aSrf.get();
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsSurface_Degree(const Naive_Handle_t hd,
                                       int *const degree_u,
                                       int *const degree_v) {
  Naive_H_CAST_AND_CHECK(const Naive_NurbsSurface, hd, H);
  if (degree_u)
    *degree_u = H->UDegree();
  if (degree_v)
    *degree_v = H->VDegree();
  return Naive_Ok;
}

Naive_Code_t Naive_NurbsSurface_Evaluate(const Naive_Handle_t hd,
                                         const double u, const double v,
                                         int n_derivative, int *const n_result,
                                         Naive_Vector3d_t *const result) {
  if (!n_result)
    return Naive_NullException;

  if (n_derivative < 0)
    return Naive_InvalidValue;

  *n_result = (n_derivative + 1) * (n_derivative + 2) >> 1;

  if (result) {
    Naive_H_CAST_AND_CHECK(const Naive_NurbsSurface, hd, H);
    Naive_Vector3dList aD{};
    if (!H->Evaluate(u, v, n_derivative, aD))
      return Naive_Err;

    for (Naive_Integer i = 0; i < *n_result; ++i) {
      aD[i].Dump(result[i]);
    }
  }

  return Naive_Ok;
}

/// }}}

/// Naive_Poly {{{

Naive_Code_t Naive_Poly_New(const int n_vertices,
                            const Naive_Point3d_t *vertices,
                            const int n_triangles,
                            const Naive_Triangle_t *triangles,
                            Naive_Handle_t *const poly) {
  if (!vertices || !triangles || !poly)
    return Naive_NullException;

  if (n_vertices < 0 || n_triangles < 0)
    return Naive_Err;

  Naive_Point3dList aVerts(n_vertices);
  for (int i = 0; i < n_vertices; ++i) {
    aVerts[i] = vertices[i];
  }

  Naive_List<Naive_Triangle> aTris(n_triangles);
  for (int i = 0; i < n_triangles; ++i) {
    aTris[i].x() = triangles[i].n0;
    aTris[i].y() = triangles[i].n1;
    aTris[i].z() = triangles[i].n2;
  }

  Handle_Naive_Poly aPoly =
      new Naive_Poly(::std::move(aVerts), ::std::move(aTris));
  aPoly->IncrementRefCounter();
  *poly = aPoly.get();
  return Naive_Ok;
}

Naive_Code_t Naive_Poly_IsValid(const Naive_Handle_t hd,
                                Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Poly, hd, H);
  *is_valid = H->IsValid();
  return Naive_Ok;
}

Naive_Code_t Naive_Poly_Clone(const Naive_Handle_t hd,
                              Naive_Handle_t *const clone) {
  if (!clone)
    return Naive_NullException;

  Naive_H_CAST(const Naive_Poly, hd, H);
  if (!H)
    return Naive_InvalidHandle;

  Handle_Naive_Poly aClone = new Naive_Poly(*H);
  aClone->IncrementRefCounter();
  *clone = aClone.get();
  return Naive_Ok;
}

Naive_Code_t Naive_Poly_Vertices(const Naive_Handle_t hd, int *const n_vertices,
                                 Naive_Point3d_t *const vertices) {
  if (!n_vertices)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Poly, hd, H);
  int nbVerts = static_cast<int>(H->Vertices().size());
  *n_vertices = nbVerts;

  if (vertices) {
    for (Naive_Size i = 0; i < nbVerts; ++i) {
      H->Vertices()[i].Dump(vertices[i]);
    }
  }

  return Naive_Ok;
}

Naive_Code_t Naive_Poly_Triangles(const Naive_Handle_t hd,
                                  int *const n_triangles,
                                  Naive_Triangle_t *const triangles) {
  if (!n_triangles)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Poly, hd, H);
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

  return Naive_Ok;
}

/// }}}

/// Naive_BndShape_ConvexHull2D {{{

Naive_Code_t
Naive_BndShape_ConvexHull2D_New(int n_points, const Naive_Point2d_t *points,
                                Naive_ConvexHull2D_Algorithm algo,
                                Naive_Handle_t *const convex_hull_2d) {
  if (!points || !convex_hull_2d)
    return Naive_NullException;

  if (n_points < 0)
    return Naive_Err;

  Naive_Point2dList aPoints(n_points);
  for (Naive_Integer i = 0; i < n_points; ++i) {
    aPoints[i] = points[i];
  }

  Naive_Handle<::naivecgl::bndshape::ConvexHull2D> aCH2D =
      new ::naivecgl::bndshape::ConvexHull2D(::std::move(aPoints), algo);
  aCH2D->IncrementRefCounter();
  *convex_hull_2d = aCH2D.get();
  return Naive_Ok;
}

Naive_Code_t
Naive_BndShape_ConvexHull2D_SetAlgorithm(Naive_Handle_t hd,
                                         Naive_ConvexHull2D_Algorithm algo) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, hd, H);
  H->SetAlgorithm(algo);
  return H->Status();
}

Naive_Code_t Naive_BndShape_ConvexHull2D_Perform(Naive_Handle_t hd) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, hd, H);
  H->Perform();
  return H->Status();
}

Naive_Code_t Naive_BndShape_ConvexHull2D_Add(Naive_Handle_t hd,
                                             Naive_Point2d_t point,
                                             Naive_Logical_t to_perform) {
  Naive_H_CAST_AND_CHECK(::naivecgl::bndshape::ConvexHull2D, hd, H);
  H->Add(point, to_perform);
  return H->Status();
}

Naive_Code_t Naive_BndShape_ConvexHull2D_Result(
    const Naive_Handle_t hd, int *const n_convex_points,
    int *const convex_indices, Naive_Point2d_t *const convex_points) {
  if (!n_convex_points)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const ::naivecgl::bndshape::ConvexHull2D, hd, H);
  if (H->Status() != Naive_Ok)
    return H->Status();

  *n_convex_points = H->NbConvexPoints();

  if (convex_indices) {
    Naive_IntegerList anIndices = H->ConvexIndices();
    ::std::copy(anIndices.cbegin(), anIndices.cend(), convex_indices);
  }

  if (convex_points) {
    Naive_Point2dList aPoints = H->ConvexPoints();
    for (Naive_Integer i = 0; i < aPoints.size(); ++i) {
      aPoints[i].Dump(convex_points[i]);
    }
  }

  return Naive_Ok;
}

/// }}}

/// Naive_BndShape_EnclosingDisc {{{

Naive_Code_t
Naive_BndShape_EnclosingDisc_New(Naive_Handle_t *const enclosing_disc) {
  if (!enclosing_disc)
    return Naive_NullException;

  Naive_Handle<::naivecgl::bndshape::EnclosingDisc> aED =
      new ::naivecgl::bndshape::EnclosingDisc();
  aED->IncrementRefCounter();
  *enclosing_disc = aED.get();
  return Naive_Ok;
}

Naive_Code_t
Naive_BndShape_EnclosingDisc_Rebuild(Naive_Handle_t hd, int n_points,
                                     const Naive_Point2d_t *points) {
  if (!points)
    return Naive_NullException;

  if (n_points < 0)
    return Naive_InvalidValue;

  Naive_H_CAST(::naivecgl::bndshape::EnclosingDisc, hd, H);
  Naive_Point2dList aPoints(points, points + n_points);
  H->ReBuild(aPoints);
  return Naive_Ok;
}

Naive_Code_t
Naive_BndShape_EnclosingDisc_Circle(const Naive_Handle_t hd,
                                    Naive_Point2d_t *const theOrigin,
                                    double *const theR) {
  if (!theOrigin || !theR)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const ::naivecgl::bndshape::EnclosingDisc, hd, H);
  Naive_Point2d anOrigin;
  Naive_Real aR;
  if (!H->Circle(anOrigin, aR))
    return Naive_Err;

  anOrigin.Dump(*theOrigin);
  *theR = aR;
  return Naive_Ok;
}

/// }}}

/// Naive_Intersect_Intersection {{{

Naive_Code_t
Naive_Intersect_Intersection_LinePlane(const Naive_Handle_t theLine,
                                       const Naive_Handle_t thePlane,
                                       double *const theT) {
  if (!theT)
    return Naive_NullException;

  Naive_H_CAST_AND_CHECK(const Naive_Line, theLine, HL);
  Naive_H_CAST_AND_CHECK(const Naive_Plane, thePlane, HP);
  return ::naivecgl::intersect::Intersection::LinePlane(*HL, *HP, *theT);
}

/// }}}

/// Naive_Tessellation_Sphere {{{

Naive_Code_t Naive_Tessellation_TetraSphere(const Naive_Point3d_t *center,
                                            double radius, int level,
                                            Naive_Handle_t *const poly) {
  if (!center || !poly)
    return Naive_NullException;

  if (radius <= ::naivecgl::math::Constant::ZeroTolerance() || level < 0)
    return Naive_InvalidValue;

  Naive_Point3d aCenter{*center};
  Handle_Naive_Poly aPoly =
      ::naivecgl::tessellation::TetraSphere(aCenter, radius, level);
  if (!aPoly)
    return Naive_Err;

  aPoly->IncrementRefCounter();
  *poly = aPoly.get();
  return Naive_Ok;
}

/// }}}

// vim: set foldmarker={{{,}}} foldmethod=marker foldlevel=0:
