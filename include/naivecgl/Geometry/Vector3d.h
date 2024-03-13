#ifndef _NaiveCGL_Geometry_Vector3d_HeaderFile
#define _NaiveCGL_Geometry_Vector3d_HeaderFile

#include <naivecgl/Geometry/Point3d.h>

Naive_NAMESPACE_BEGIN(geometry);

class Vector3d final {
public:
  Naive_EXPORT Vector3d();

  Naive_EXPORT Vector3d(const Naive_Real theX, const Naive_Real theY,
                        const Naive_Real theZ);

  Naive_EXPORT Vector3d(const Naive_XYZ &theXYZ);

  Naive_EXPORT Vector3d(const Naive_Vector3d_T &theVec);

  Naive_EXPORT static const Vector3d &Unset();

  Naive_EXPORT const Naive_XYZ &XYZ() const { return myXYZ; }

  Naive_EXPORT Naive_XYZ &ChangeXYZ() { return myXYZ; }

  Naive_EXPORT Naive_Real X() const { return myXYZ.x(); }

  Naive_EXPORT Naive_Real Y() const { return myXYZ.y(); }

  Naive_EXPORT Naive_Real Z() const { return myXYZ.z(); }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool IsZero() const { return myXYZ.isZero(); }

  Naive_EXPORT void Normalize() { myXYZ.normalize(); }

  Naive_EXPORT Vector3d Crossed(const Vector3d &theVec) const {
    return myXYZ.cross(theVec.myXYZ);
  }

private:
  Naive_Vector3<Naive_Real> myXYZ;
};

Naive_NAMESPACE_END(geometry);

using Naive_Vector3d = naivecgl::geometry::Vector3d;
using Naive_Vector3d_List = Naive_List<Naive_Vector3d>;

#endif
