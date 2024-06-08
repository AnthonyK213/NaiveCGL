#ifndef _NaiveCGL_Geometry_Surface_HeaderFile
#define _NaiveCGL_Geometry_Surface_HeaderFile

#include "Geometry.h"
#include "Point3d.h"
#include "Vector3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Surface : public Geometry {
public:
  Naive_EXPORT virtual Naive_Point3d PointAt(const Naive_Real theU,
                                             const Naive_Real theV) const = 0;

  Naive_EXPORT virtual Naive_Code Evaluate(const Naive_Real theU,
                                           const Naive_Real theV,
                                           const Naive_Integer theN,
                                           Naive_Vector3dList &theD) const = 0;
};

Naive_NAMESPACE_END(geometry);

using Naive_Surface = ::naivecgl::geometry::Surface;
Naive_DEFINE_HANDLE(Naive_Surface);

#endif
