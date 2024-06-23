#ifndef _NaiveCGL_Geometry_Curve_HeaderFile
#define _NaiveCGL_Geometry_Curve_HeaderFile

#include "../Math/Pnt3d.h"
#include "../Math/Vec3d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry);

class Curve : public Naive_Geometry {
public:
  Naive_EXPORT virtual Naive_Real FirstParameter() const = 0;

  Naive_EXPORT virtual Naive_Real LastParameter() const = 0;

  Naive_EXPORT virtual Naive_Pnt3d PointAt(const Naive_Real theT) const = 0;

  Naive_EXPORT virtual Naive_Vec3d TangentAt(const Naive_Real theT) const = 0;

  Naive_EXPORT virtual Naive_Code
  DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
               Naive_Vec3dList1 &theD) const = 0;

  Naive_EXPORT virtual Naive_Code CurvatureAt(const Naive_Real theT,
                                              Naive_Vec3d &theV) const = 0;
};

Naive_NAMESPACE_END(geometry);

using Naive_Curve = ::naivecgl::geometry::Curve;
Naive_DEFINE_HANDLE(Naive_Curve);

#endif
