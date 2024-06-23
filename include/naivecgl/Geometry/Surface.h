#ifndef _NaiveCGL_Geometry_Surface_HeaderFile
#define _NaiveCGL_Geometry_Surface_HeaderFile

#include "../Math/Pnt3d.h"
#include "../Math/Vec3d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry);

class Surface : public Naive_Geometry {
public:
  Naive_EXPORT virtual Naive_Pnt3d PointAt(const Naive_Real theU,
                                           const Naive_Real theV) const = 0;

  Naive_EXPORT virtual Naive_Code Evaluate(const Naive_Real theU,
                                           const Naive_Real theV,
                                           const Naive_Integer theN,
                                           Naive_Vec3dList1 &theD) const = 0;
};

Naive_NAMESPACE_END(geometry);

using Naive_Surface = ::naivecgl::geometry::Surface;
Naive_DEFINE_HANDLE(Naive_Surface);

#endif
