#ifndef _NaiveCGL_BRep_PointOnCurve_HeaderFile
#define _NaiveCGL_BRep_PointOnCurve_HeaderFile

#include "PointRep.h"

Naive_NAMESPACE_BEGIN(geometry);

class Curve;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(brep);

class PointOnCurve final : public PointRep {
public:
  Naive_EXPORT PointOnCurve(const Naive_Handle<geometry::Curve> &theCrv,
                            const Naive_Real theT);

  Naive_EXPORT virtual Naive_Pnt3d Pnt() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real X() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real Y() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real Z() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

protected:
  Naive_EXPORT virtual Naive_Code
  transform(const math::Trsf3d &theTrsf) Naive_OVERRIDE;

private:
  Naive_Handle<geometry::Curve> myCrv;
  Naive_Real myT;
};

Naive_NAMESPACE_END(brep);

#endif
