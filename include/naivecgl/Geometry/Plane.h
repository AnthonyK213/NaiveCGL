#ifndef _NaiveCGL_Geometry_Plane_HeaderFile
#define _NaiveCGL_Geometry_Plane_HeaderFile

#include "../Math/Pln.h"
#include "Surface.h"

Naive_NAMESPACE_BEGIN(geometry);

class Plane final : public Naive_Surface {
public:
  Naive_EXPORT Plane();

  Naive_EXPORT Plane(const Naive_Pln &thePln);

  const Naive_Pln &Pln() const { return myPln; }

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d
  PointAt(const Naive_Real theU, const Naive_Real theV) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theU, const Naive_Real theV,
           const Naive_Integer theN,
           Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

  Naive_EXPORT Naive_Real Distance(const Naive_Pnt3d &theP) const;

private:
  Naive_Pln myPln;
};

Naive_NAMESPACE_END(geometry);

using Naive_Plane = ::naivecgl::geometry::Plane;
Naive_DEFINE_HANDLE(Naive_Plane);

#endif
