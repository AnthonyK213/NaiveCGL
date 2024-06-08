#ifndef _NaiveCGL_Geometry_Plane_HeaderFile
#define _NaiveCGL_Geometry_Plane_HeaderFile

#include "Geometry.h"
#include "Point3d.h"
#include "Transform3d.h"
#include "Vector3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Plane final : public Geometry {
public:
  Naive_EXPORT Plane();

  Naive_EXPORT Plane(const Naive_Point3d &thePoint,
                     const Naive_Vector3d &theXAxis,
                     const Naive_Vector3d &theYAxis);

  Naive_EXPORT Plane(const Naive_Point3d &thePoint,
                     const Naive_Vector3d &theNormal);

  Naive_EXPORT Plane(const Naive_Plane_t &thePlaneT);

  Naive_EXPORT virtual Naive_Bool IsValid() const override;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const override;

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

  Naive_EXPORT Naive_Bool Dump(Naive_Plane_t &thePlaneT) const;

  Naive_EXPORT Naive_Bool Orient(const Plane &thePln,
                                 Transform3d &theTrsf) const;

private:
  void initInvalid();

  Naive_Bool initByXY();

  Naive_Bool initByZX();

private:
  Naive_Point3d myLocation;
  Naive_Vector3d myXAxis;
  Naive_Vector3d myYAxis;
  Naive_Vector3d myZAxis;
};

Naive_NAMESPACE_END(geometry);

using Naive_Plane = ::naivecgl::geometry::Plane;
Naive_DEFINE_HANDLE(Naive_Plane);

#endif
