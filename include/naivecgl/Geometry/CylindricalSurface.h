#ifndef _NaiveCGL_Geometry_CylindricalSurface_HeaderFile
#define _NaiveCGL_Geometry_CylindricalSurface_HeaderFile

#include "ElementarySurface.h"

Naive_NAMESPACE_BEGIN(geometry);

class CylindricalSurface final : public Naive_ElementarySurface {
public:
  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d
  PointAt(const Naive_Real theU, const Naive_Real theV) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theU, const Naive_Real theV,
           const Naive_Integer theN,
           Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(CylindricalSurface, Naive_ElementarySurface);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_CylindricalSurface = ::naivecgl::geometry::CylindricalSurface;
Naive_DEFINE_HANDLE(Naive_CylindricalSurface);

#endif
