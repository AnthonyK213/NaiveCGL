#ifndef _NaiveCGL_Geometry_Plane_HeaderFile
#define _NaiveCGL_Geometry_Plane_HeaderFile

#include "Point3d.h"
#include "Transform3d.h"
#include "Vector3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Plane final {
public:
  Naive_EXPORT Plane();

  Naive_EXPORT Plane(const Naive_Point3d &thePoint,
                     const Naive_Vector3d &theXAxis,
                     const Naive_Vector3d &theYAxis);

  Naive_EXPORT Plane(const Naive_Point3d &thePoint,
                     const Naive_Vector3d &theNormal);

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT const Naive_Point3d &Location() const { return myLocation; }

  Naive_EXPORT const Naive_Vector3d &XAxis() const { return myXAxis; }

  Naive_EXPORT const Naive_Vector3d &YAxis() const { return myYAxis; }

  Naive_EXPORT const Naive_Vector3d &Axis() const { return myZAxis; }

  Naive_EXPORT Naive_Real Distance(const Naive_Point3d &thePoint) const;

  Naive_EXPORT static const Plane &Unset();

  Naive_EXPORT static const Plane &WorldXY();

  Naive_EXPORT static const Plane &WorldYZ();

  Naive_EXPORT static const Plane &WorldZX();

  Naive_EXPORT Naive_Bool Transform(const Transform3d &theTrsf);

  Naive_EXPORT Plane Transformed(const Transform3d &theTrsf) const;

  Naive_EXPORT Naive_Bool Orient(const Plane &thePln,
                                 Transform3d &theTrsf) const;

private:
  void initByXY();

private:
  Naive_Point3d myLocation;
  Naive_Vector3d myXAxis;
  Naive_Vector3d myYAxis;
  Naive_Vector3d myZAxis;
};

Naive_NAMESPACE_END(geometry);

using Naive_Plane = ::naivecgl::geometry::Plane;

#endif
