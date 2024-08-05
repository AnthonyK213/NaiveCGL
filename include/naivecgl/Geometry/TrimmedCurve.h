#ifndef _NaiveCGL_Geometry_TrimmedCurve_HeaderFile
#define _NaiveCGL_Geometry_TrimmedCurve_HeaderFile

#include "BoundedCurve.h"

Naive_NAMESPACE_BEGIN(geometry);

class TrimmedCurve : public Naive_BoundedCurve {
public:
  TrimmedCurve(const Handle_Naive_Curve &theCurve, const Naive_Real theT1,
               const Naive_Real theT2);

  const Handle_Naive_Curve &BasisCurve() const { return myBasisCurve; }

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real FirstParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real LastParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d
  PointAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Vec3d
  TangentAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theT, const Naive_Integer theN,
           Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  CurvatureAt(const Naive_Real theT, Naive_Vec3d &theV) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d EndPoint() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d StartPoint() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(TrimmedCurve, Naive_BoundedCurve);

private:
  Handle_Naive_Curve myBasisCurve;
  Naive_Real myT1;
  Naive_Real myT2;
};

Naive_NAMESPACE_END(geometry);

using Naive_TrimmedCurve = ::naivecgl::geometry::TrimmedCurve;
Naive_DEFINE_HANDLE(Naive_TrimmedCurve);

#endif
