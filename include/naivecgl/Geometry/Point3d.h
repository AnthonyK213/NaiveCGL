#ifndef _NaiveCGL_Geometry_Point3d_HeaderFile
#define _NaiveCGL_Geometry_Point3d_HeaderFile

#include <naivecgl/Common/Macro.h>
#include <naivecgl/Common/Type.h>

Naive_NAMESPACE_BEGIN(geometry);

class Vector3d;
class Transform3d;

class Point3d final {
public:
  Naive_EXPORT Point3d();

  Naive_EXPORT Point3d(const Naive_Real theX, const Naive_Real theY,
                       const Naive_Real theZ);

  Naive_EXPORT Point3d(const Naive_XYZ &theXYZ);

  Naive_EXPORT Point3d(const Naive_Point3d_T &thePnt);

  Naive_EXPORT static const Point3d &Origin();

  Naive_EXPORT static const Point3d &Unset();

  Naive_EXPORT const Naive_XYZ &XYZ() const { return myXYZ; }

  Naive_EXPORT Naive_XYZ &ChangeXYZ() { return myXYZ; }

  Naive_EXPORT Naive_Real X() const { return myXYZ.x(); }

  Naive_EXPORT Naive_Real Y() const { return myXYZ.y(); }

  Naive_EXPORT Naive_Real Z() const { return myXYZ.z(); }

  Naive_EXPORT void SetX(const Naive_Real theX) { myXYZ.x() = theX; }

  Naive_EXPORT void SetY(const Naive_Real theY) { myXYZ.y() = theY; }

  Naive_EXPORT void SetZ(const Naive_Real theZ) { myXYZ.z() = theZ; }

  Naive_EXPORT void SetXYZ(const Naive_Real theX, const Naive_Real theY,
                           const Naive_Real theZ);

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Real DistanceTo(const Point3d &thePoint) const;

  Naive_EXPORT Naive_Real DistanceToSquared(const Point3d &thePoint) const;

  Naive_EXPORT Naive_Bool Add(const Point3d &thePoint);

  Naive_EXPORT Point3d Added(const Point3d &thePoint) const;

  Naive_EXPORT Naive_Bool Add(const Vector3d &theVector);

  Naive_EXPORT Point3d Added(const Vector3d &theVector) const;

  Naive_EXPORT Vector3d Subtracted(const Point3d &thePoint) const;

  Naive_EXPORT Naive_Bool Multiply(const Naive_Real &theT);

  Naive_EXPORT Point3d Multiplied(const Naive_Real &theT) const;

  Naive_EXPORT Naive_Bool Divide(const Naive_Real &theT);

  Naive_EXPORT Point3d Divided(const Naive_Real &theT) const;

  Naive_EXPORT void Negate();

  Naive_EXPORT Point3d Negated() const;

  Naive_EXPORT Naive_Bool Transform(const Transform3d &theTrsf);

  Naive_EXPORT Point3d Transformed(const Transform3d &theTrsf) const;

  Naive_EXPORT Naive_Integer CompareTo(const Point3d &thePoint) const;

  Naive_EXPORT Naive_Bool Dump(Naive_Point3d_T &theP) const;

private:
  Naive_XYZ myXYZ;
};

Naive_EXPORT const Point3d operator+(const Point3d &thePnt1,
                                     const Point3d &thePnt2);

Naive_EXPORT const Point3d operator+(const Point3d &thePnt,
                                     const Vector3d &theVec);

Naive_EXPORT const Vector3d operator-(const Point3d &thePnt1,
                                      const Point3d &thePnt2);

Naive_EXPORT const Point3d operator-(const Point3d &thePnt);

Naive_EXPORT const Point3d operator*(const Point3d &thePnt,
                                     const Naive_Real theT);

Naive_EXPORT const Point3d operator*(const Naive_Real theT,
                                     const Point3d &thePnt);

Naive_EXPORT const Point3d operator/(const Point3d &thePnt,
                                     const Naive_Real theT);

Naive_NAMESPACE_END(geometry);

using Naive_Point3d = ::naivecgl::geometry::Point3d;
using Naive_Point3dList = Naive_List<Naive_Point3d>;
using Naive_Point3dList2 = Naive_List2<Naive_Point3d>;

#endif
