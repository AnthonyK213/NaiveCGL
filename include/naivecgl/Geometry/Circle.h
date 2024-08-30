#ifndef _NaiveCGL_Geometry_Circle_HeaderFile
#define _NaiveCGL_Geometry_Circle_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry);

class Circle final : public Naive_Conic {
public:
  Naive_EXPORT Circle();

  Naive_EXPORT Circle(const Naive_Ax2 &theAx2, const Naive_Real theR);

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

  Naive_EXPORT virtual Naive_Bool IsClosed() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsPeriodic() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real Period() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Circle, Naive_Conic);

private:
  Naive_Real myRadius;
};

Naive_NAMESPACE_END(geometry);

using Naive_Circle = ::naivecgl::geometry::Circle;
Naive_DEFINE_HANDLE(Naive_Circle);

#endif
