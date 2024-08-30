#ifndef _NaiveCGL_Geometry2d_Line_HeaderFile
#define _NaiveCGL_Geometry2d_Line_HeaderFile

#include "../Math/Ax2d.h"
#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Line : public Naive_Curve2d {
public:
  Naive_EXPORT Line(const Naive_Ax2d &thePos) noexcept;

  Naive_EXPORT Line(const Naive_Pnt2d &theLocation,
                    const Naive_Vec2d &theDirection);

  Naive_EXPORT Line(const Naive_Line2d_sf_t &theLine2dSF);

  Naive_EXPORT const Naive_Ax2d &Position() { return myPos; }

  Naive_EXPORT virtual Naive_Real FirstParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real LastParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry2d Clone() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Real DistanceTo(const Naive_Pnt2d &thePnt) const;

  Naive_EXPORT virtual Naive_Pnt2d
  PointAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Vec2d
  TangentAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theT, const Naive_Integer theN,
           Naive_Vec2dList1 &theD) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  CurvatureAt(const Naive_Real theT, Naive_Vec2d &theV) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsClosed() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsPeriodic() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real Period() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Lines, Naive_Curve2d);

private:
  Naive_Ax2d myPos;
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Line2d = ::naivecgl::geometry2d::Line;
Naive_DEFINE_HANDLE(Naive_Line2d);

#endif
