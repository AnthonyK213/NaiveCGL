#ifndef _NaiveCGL_BRep_PointOnSurface_HeaderFile
#define _NaiveCGL_BRep_PointOnSurface_HeaderFile

#include "PointRep.h"

Naive_NAMESPACE_BEGIN(geometry);

class Surface;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(brep);

class PointOnSurface final : public PointRep {
public:
  Naive_EXPORT PointOnSurface(const Naive_Handle<geometry::Surface> &theSrf,
                              const Naive_Real theU, const Naive_Real theV);

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
  Naive_Handle<geometry::Surface> mySrf;
  Naive_Real myU;
  Naive_Real myV;
};

Naive_NAMESPACE_END(brep);

#endif
