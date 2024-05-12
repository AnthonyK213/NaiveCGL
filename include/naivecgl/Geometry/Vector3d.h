#ifndef _NaiveCGL_Geometry_Vector3d_HeaderFile
#define _NaiveCGL_Geometry_Vector3d_HeaderFile

#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(geometry);

class Point3d;
class Transform3d;

class Vector3d final {
public:
  Naive_EXPORT Vector3d();

  Naive_EXPORT explicit Vector3d(const Point3d &thePoint);

  Naive_EXPORT Vector3d(const Naive_Real theX, const Naive_Real theY,
                        const Naive_Real theZ);

  Naive_EXPORT Vector3d(const Naive_XYZ &theXYZ);

  Naive_EXPORT Vector3d(const Naive_Vector3d_T &theVec);

  Naive_EXPORT const Naive_XYZ &XYZ() const { return myXYZ; }

  Naive_EXPORT Naive_XYZ &ChangeXYZ() { return myXYZ; }

  Naive_EXPORT Naive_Real X() const { return myXYZ.x(); }

  Naive_EXPORT Naive_Real Y() const { return myXYZ.y(); }

  Naive_EXPORT Naive_Real Z() const { return myXYZ.z(); }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool IsUnitVector() const;

  Naive_EXPORT Naive_Bool IsZero() const;

  Naive_EXPORT Naive_Real Length() const;

  Naive_EXPORT Naive_Real SquareLength() const;

  Naive_EXPORT static const Vector3d &XAxis();

  Naive_EXPORT static const Vector3d &YAxis();

  Naive_EXPORT static const Vector3d &ZAxis();

  Naive_EXPORT static const Vector3d &Zero();

  Naive_EXPORT static const Vector3d &Unset();

  Naive_EXPORT Naive_Bool Normalize();

  Naive_EXPORT Vector3d Normalized() const;

  Naive_EXPORT Naive_Bool Add(const Vector3d &theVec);

  Naive_EXPORT Vector3d Added(const Vector3d &theVec) const;

  Naive_EXPORT Naive_Bool Subtract(const Vector3d &theVec);

  Naive_EXPORT Vector3d Subtracted(const Vector3d &theVec) const;

  Naive_EXPORT Naive_Bool Multiply(const Naive_Real theT);

  Naive_EXPORT Vector3d Multiplied(const Naive_Real theT) const;

  Naive_EXPORT Naive_Bool Divide(const Naive_Real theT);

  Naive_EXPORT Vector3d Divided(const Naive_Real theT) const;

  Naive_EXPORT void Negate();

  Naive_EXPORT Vector3d Negated() const;

  Naive_EXPORT Naive_Real Dot(const Vector3d &theVec) const;

  Naive_EXPORT void Cross(const Vector3d &theVec);

  Naive_EXPORT Vector3d Crossed(const Vector3d &theVec) const;

  Naive_EXPORT Naive_Bool Reverse();

  Naive_EXPORT Naive_Bool
  EpsilonEquals(const Vector3d &theVec,
                const Naive_Real theE = math::Constant::Epsilon());

  Naive_EXPORT Naive_Bool Equals(const Vector3d &theVec);

  Naive_EXPORT Naive_Bool Transform(const Transform3d &theTrsf);

  Naive_EXPORT Vector3d Transformed(const Transform3d &theTrsf) const;

  Naive_EXPORT Naive_Bool Dump(Naive_Vector3d_T &theVec) const;

private:
  Naive_XYZ myXYZ;
};

Naive_EXPORT const Vector3d operator+(const Vector3d &theVec1,
                                      const Vector3d &theVec2);

Naive_EXPORT const Vector3d operator-(const Vector3d &theVec1,
                                      const Vector3d &theVec2);

Naive_EXPORT const Vector3d operator-(const Vector3d &theVec);

Naive_EXPORT const Vector3d operator*(const Vector3d &theVec,
                                      const Naive_Real theT);

Naive_EXPORT const Vector3d operator*(const Naive_Real theT,
                                      const Vector3d &theVec);

Naive_EXPORT const Naive_Real operator*(const Vector3d theVec1,
                                        const Vector3d &theVec2);

Naive_EXPORT const Vector3d operator/(const Vector3d &theVec,
                                      const Naive_Real theT);

Naive_NAMESPACE_END(geometry);

using Naive_Vector3d = ::naivecgl::geometry::Vector3d;
using Naive_Vector3dList = Naive_List<Naive_Vector3d>;
using Naive_Vector3dList2 = Naive_List2<Naive_Vector3d>;

#endif
