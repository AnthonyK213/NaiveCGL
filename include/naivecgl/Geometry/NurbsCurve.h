#ifndef _NaiveCGL_Geometry_NurbsCurve_HeaderFile
#define _NaiveCGL_Geometry_NurbsCurve_HeaderFile

#include "../Math/Nurbs.h"
#include "../Math/Util.h"
#include "BoundedCurve.h"

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve final : public Naive_BoundedCurve {
public:
  Naive_EXPORT NurbsCurve() noexcept;

  Naive_EXPORT NurbsCurve(const Naive_Pnt3dList1 &thePoles,
                          const Naive_RealList1 &theWeights,
                          const Naive_RealList1 &theKnots,
                          const Naive_IntegerList1 &theMults,
                          const Naive_Integer theDegree) noexcept;

  Naive_EXPORT Naive_Code Init(const Naive_Pnt3dList1 &thePoles,
                               const Naive_RealList1 &theWeights,
                               const Naive_RealList1 &theKnots,
                               const Naive_IntegerList1 &theMults,
                               const Naive_Integer theDegree) noexcept;

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Integer Degree() const { return myDegree; }

  Naive_EXPORT Naive_Integer NbPoles() const;

  Naive_EXPORT const Naive_Pnt3d &Pole(const Naive_Integer theIndex) const;

  Naive_EXPORT const Naive_Pnt3dList1 &Poles() const { return myPoles; }

  Naive_EXPORT Naive_Real Weight(const Naive_Integer theIndex) const;

  Naive_EXPORT const Naive_RealList1 &Weights() const { return myWeights; }

  Naive_EXPORT Naive_Integer NbKnots() const;

  Naive_EXPORT Naive_Real Knot(const Naive_Integer theIndex) const;

  Naive_EXPORT const Naive_RealList1 &Knots() const { return myKnots; }

  Naive_EXPORT Naive_Integer Multiplicity(const Naive_Integer theIndex) const;

  Naive_EXPORT const Naive_IntegerList1 &Multiplicities() const {
    return myMults;
  }

  Naive_EXPORT virtual Naive_Real FirstParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real LastParameter() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Bool IsRational() const { return myRational; }

  Naive_EXPORT Naive_Bool IsPeriodic() const { return myPeriodic; }

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theT, const Naive_Integer theN,
           Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  CurvatureAt(const Naive_Real theT, Naive_Vec3d &theV) const Naive_OVERRIDE;

  Naive_EXPORT Naive_Code RaiseDegree(const Naive_Integer theDegree);

  Naive_EXPORT Naive_Code IncreaseMultiplicity(const Naive_Integer theI,
                                               const Naive_Integer theM);

  Naive_EXPORT Naive_Code InsertKnot(const Naive_Real theT,
                                     const Naive_Integer theM);

  /**
   * @brief Reduces the multiplicity of the knot of index |I| to |M|.
   *
   * @param theI The knot index.
   * @param theM The multiplicity to reduce to.
   * @return If reduced successfully, true; otherwise, false.
   */
  Naive_EXPORT Naive_Code RemoveKnot(const Naive_Integer theI,
                                     const Naive_Integer theM);

  Naive_EXPORT virtual Naive_Pnt3d EndPoint() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d StartPoint() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(NurbsCurve, Naive_BoundedCurve);

protected:
  Naive_EXPORT virtual Naive_Code
  transform(const math::Trsf3d &theTrsf) Naive_OVERRIDE;

private:
  template <typename P, typename Rw, typename Rk, typename I>
  Naive_Code update(P &&thePoles, Rw &&theWeights, Rk &&theKnots, I &&theMults,
                    const Naive_Integer theDegree);

private:
  Naive_Bool myRational;
  Naive_Bool myPeriodic;
  Naive_Integer myDegree;
  Naive_Pnt3dList1 myPoles;
  Naive_RealList1 myWeights;
  Naive_RealList1 myFlatKnots;
  Naive_RealList1 myKnots;
  Naive_IntegerList1 myMults;
  Naive_IntegerList1 mySpanIdx;
};

Naive_NAMESPACE_END(geometry);

#include "detail/NurbsCurve.inl"

using Naive_NurbsCurve = ::naivecgl::geometry::NurbsCurve;
Naive_DEFINE_HANDLE(Naive_NurbsCurve);

#endif
