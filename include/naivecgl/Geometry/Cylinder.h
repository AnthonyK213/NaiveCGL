#ifndef _NaiveCGL_Geometry_Cylinder_HeaderFile
#define _NaiveCGL_Geometry_Cylinder_HeaderFile

#include "../Math/Pln.h"
#include "Surface.h"

Naive_NAMESPACE_BEGIN(geometry);

class Cylinder final : public Naive_Surface {
public:
  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Pnt3d
  PointAt(const Naive_Real theU, const Naive_Real theV) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theU, const Naive_Real theV,
           const Naive_Integer theN,
           Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_Cylinder = ::naivecgl::geometry::Cylinder;
Naive_DEFINE_HANDLE(Naive_Cylinder);

#endif
