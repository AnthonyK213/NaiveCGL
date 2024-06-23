#ifndef _NaiveCGL_Geometry_Circle_HeaderFile
#define _NaiveCGL_Geometry_Circle_HeaderFile

#include "../Math/Pln.h"
#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry);

class Circle final : public Naive_Curve {
public:
  Naive_EXPORT Circle();

  Naive_EXPORT Circle(const Naive_Pln &thePln, const Naive_Real theRadius);

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real FirstParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real LastParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d
  PointAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Vec3d
  TangentAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
               Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  CurvatureAt(const Naive_Real theT, Naive_Vec3d &theV) const Naive_OVERRIDE;

private:
  Naive_Pln myPln;
  Naive_Real myRadius;
};

Naive_NAMESPACE_END(geometry);

using Naive_Circle = ::naivecgl::geometry::Circle;

#endif
