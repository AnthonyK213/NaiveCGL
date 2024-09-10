#ifndef _NaiveCGL_BRep_CurveOnSurface_HeaderFile
#define _NaiveCGL_BRep_CurveOnSurface_HeaderFile

#include "CurveRep.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Curve;

Naive_NAMESPACE_END(geometry2d);

Naive_NAMESPACE_BEGIN(geometry);

class Surface;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(brep);

class CurveOnSurface final : public CurveRep {
public:
  Naive_EXPORT CurveOnSurface(const Naive_Handle<geometry::Surface> &theSrf,
                              const Naive_Handle<geometry2d::Curve> &thePCrv);

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

  Naive_EXPORT virtual Handle_Naive_Curve ComputeCurve3d() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(CurveOnSurface, CurveRep);

protected:
  Naive_EXPORT virtual Naive_Code
  transform(const math::Trsf3d &theTrsf) Naive_OVERRIDE;

private:
  Naive_Handle<geometry::Surface> mySrf;
  Naive_Handle<geometry2d::Curve> myPCrv;
};

Naive_NAMESPACE_END(brep);

#endif
