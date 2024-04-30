#ifndef _NaiveCGL_Geometry_Curve_HeaderFile
#define _NaiveCGL_Geometry_Curve_HeaderFile

#include "Geometry.h"
#include "Point3d.h"
#include "Vector3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Curve : public Geometry {
public:
  Naive_EXPORT virtual Naive_Real FirstParameter() const = 0;

  Naive_EXPORT virtual Naive_Real LastParameter() const = 0;

  Naive_EXPORT virtual Naive_Point3d PointAt(const Naive_Real theT) const = 0;

  Naive_EXPORT virtual Naive_Vector3d
  TangentAt(const Naive_Real theT) const = 0;

  Naive_EXPORT virtual Naive_Bool
  DerivativeAt(const Naive_Real theT, const Naive_Integer theN,
               Naive_Vector3dList &theD) const = 0;

  Naive_EXPORT virtual Naive_Vector3d
  CurvatureAt(const Naive_Real theT) const = 0;
};

Naive_NAMESPACE_END(geometry);

using Naive_Curve = ::naivecgl::geometry::Curve;
Naive_DEFINE_HANDLE(Naive_Curve);

#endif
