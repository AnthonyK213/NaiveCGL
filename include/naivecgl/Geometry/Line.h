#ifndef _NaiveCGL_Geometry_Line_HeaderFile
#define _NaiveCGL_Geometry_Line_HeaderFile

#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry);

class Line final : public Naive_Curve {
public:
  Naive_EXPORT Line() {}

  Naive_EXPORT Line(const Naive_Pnt3d &theFrom, const Naive_Pnt3d &theTo);

  Naive_EXPORT Line(const Naive_Pnt3d &theLocation,
                    const Naive_Vec3d &theDirection);

  Naive_EXPORT Line(const Naive_Line_sf_t &theLineT);

  Naive_EXPORT Naive_Pnt3d Location() const { return myLocation; }

  Naive_EXPORT Naive_Vec3d Direction() const { return myAxis; }

  Naive_EXPORT Naive_Vec3d UnitTangent() const;

  Naive_EXPORT virtual Naive_Real FirstParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real LastParameter() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Real DistanceTo(const Naive_Pnt3d &thePnt) const;

  Naive_EXPORT virtual Naive_Pnt3d
  PointAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Vec3d
  TangentAt(const Naive_Real theT) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theT, const Naive_Integer theN,
           Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  CurvatureAt(const Naive_Real theT, Naive_Vec3d &theV) const Naive_OVERRIDE;

private:
  Naive_Pnt3d myLocation;
  Naive_Vec3d myAxis;
};

Naive_NAMESPACE_END(geometry);

using Naive_Line = ::naivecgl::geometry::Line;
Naive_DEFINE_HANDLE(Naive_Line);

#endif
