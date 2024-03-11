#ifndef _NaiveCGL_Geometry_Plane_HeaderFile
#define _NaiveCGL_Geometry_Plane_HeaderFile

#include "def.h"

Naive_NAMESPACE_BEGIN(geometry);

class Plane final {
public:
  Naive_EXPORT Plane();

  Naive_EXPORT Plane(const Naive_Plane_T &thePlane);

  Naive_EXPORT Plane(const Naive_Point3d &thePoint,
                     const Naive_Vector3d &theXAxis,
                     const Naive_Vector3d &theYAxis);

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT const Naive_Point3d &Location() const { return myLocation; }

  Naive_EXPORT const Naive_Vector3d &XAxis() const { return myXAxis; }

  Naive_EXPORT const Naive_Vector3d &YAxis() const { return myYAxis; }

  Naive_EXPORT const Naive_Vector3d &Axis() const { return myZAxis; }

  Naive_EXPORT Naive_Real Distance(const Naive_Point3d &thePoint) const;

private:
  Naive_Point3d myLocation;
  Naive_Vector3d myXAxis;
  Naive_Vector3d myYAxis;
  Naive_Vector3d myZAxis;
};

Naive_NAMESPACE_END(geometry);

#endif
