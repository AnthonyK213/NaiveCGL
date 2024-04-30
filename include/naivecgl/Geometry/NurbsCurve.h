#ifndef _NaiveCGL_Geometry_NurbsCurve_HeaderFile
#define _NaiveCGL_Geometry_NurbsCurve_HeaderFile

#include "Curve.h"

#include <naivecgl/Common/Handle.h>
#include <naivecgl/Math/Nurbs.h>

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve final : public Curve {
public:
  Naive_EXPORT NurbsCurve(const Naive_Point3dList &thePoles,
                          const Naive_RealList &theWeights,
                          const Naive_RealList &theKnots,
                          const Naive_IntegerList &theMults,
                          const Naive_Integer theDegree);

  Naive_EXPORT virtual Naive_Bool IsValid() const override;

  Naive_EXPORT Naive_Integer Degree() const { return myDegree; }

  Naive_EXPORT Naive_Integer NbPoles() const;

  Naive_EXPORT const Naive_Point3d &Pole(const Naive_Integer theIndex) const;

  Naive_EXPORT Naive_Real Weight(const Naive_Integer theIndex) const;

  Naive_EXPORT Naive_Integer NbKnots() const;

  Naive_EXPORT Naive_Real Knot(const Naive_Integer theIndex) const;

  Naive_EXPORT Naive_Integer Multiplicity(const Naive_Integer theIndex) const;

  Naive_EXPORT virtual Naive_Real FirstParameter() const override;

  Naive_EXPORT virtual Naive_Real LastParameter() const override;

  Naive_EXPORT Naive_Bool IsRational() const { return myRational; }

  Naive_EXPORT Naive_Bool IsPeriodic() const { return myPeriodic; }

  Naive_EXPORT virtual Naive_Point3d
  PointAt(const Naive_Real theT) const override;

  Naive_EXPORT virtual Naive_Vector3d
  TangentAt(const Naive_Real theT) const override;

  Naive_EXPORT virtual Naive_Bool
  DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
               Naive_Vector3dList &theD) const override;

  Naive_EXPORT virtual Naive_Vector3d
  CurvatureAt(const Naive_Real theT) const override;

  Naive_EXPORT Naive_Bool IncreaseDegree(const Naive_Integer theDegree);

  Naive_EXPORT Naive_Bool IncreaseMultiplicity(const Naive_Integer theI,
                                               const Naive_Integer theM);

  Naive_EXPORT Naive_Bool InsertKnot(const Naive_Real theT,
                                     const Naive_Integer theM);

  /// @brief Reduces the multiplicity of the knot of index |I| to |M|.
  /// @param theI The knot index.
  /// @param theM The multiplicity to reduce to.
  /// @return If reduced successfully, true; otherwise, false.
  Naive_EXPORT Naive_Bool RemoveKnot(const Naive_Integer theI,
                                     const Naive_Integer theM);

private:
  template <typename P, typename Rw, typename Rk, typename I>
  Naive_Bool update(P &&thePoles, Rw &&theWeights, Rk &&theKnots, I &&theMults,
                    const Naive_Integer theDegree);

private:
  Naive_Bool myRational;
  Naive_Bool myPeriodic;
  Naive_Integer myDegree;
  Naive_Point3dList myPoles;
  Naive_RealList myWeights;
  Naive_RealList myFlatKnots;
  Naive_RealList myKnots;
  Naive_IntegerList myMults;
  Naive_IntegerList mySpanIdx;
};

Naive_NAMESPACE_END(geometry);

#include "detail/NurbsCurve.inl"

using Naive_NurbsCurve = ::naivecgl::geometry::NurbsCurve;
Naive_DEFINE_HANDLE(Naive_NurbsCurve);

#endif
