#ifndef _NaiveCGL_Math_Vec3d_HeaderFile
#define _NaiveCGL_Math_Vec3d_HeaderFile

#include "Precision.h"

Naive_NAMESPACE_BEGIN(math);

class Pnt3d;
class Trsf3d;

class Vec3d final {
public:
  Naive_EXPORT Vec3d();

  Naive_EXPORT explicit Vec3d(const Pnt3d &thePoint);

  Naive_EXPORT Vec3d(const Naive_Real theX, const Naive_Real theY,
                     const Naive_Real theZ);

  Naive_EXPORT Vec3d(const Naive_XYZ &theXYZ);

  Naive_EXPORT Vec3d(const Naive_Vector3d_t &theVec);

  Naive_EXPORT const Naive_XYZ &XYZ() const { return myXYZ; }

  Naive_EXPORT Naive_XYZ &ChangeXYZ() { return myXYZ; }

  Naive_EXPORT void SetX(const Naive_Real theX) { myXYZ.x() = theX; }

  Naive_EXPORT void SetY(const Naive_Real theY) { myXYZ.y() = theY; }

  Naive_EXPORT void SetZ(const Naive_Real theZ) { myXYZ.z() = theZ; }

  Naive_EXPORT Naive_Real X() const { return myXYZ.x(); }

  Naive_EXPORT Naive_Real Y() const { return myXYZ.y(); }

  Naive_EXPORT Naive_Real Z() const { return myXYZ.z(); }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool IsUnitVector() const;

  Naive_EXPORT Naive_Bool IsZero() const;

  Naive_EXPORT Naive_Real Length() const;

  Naive_EXPORT Naive_Real SquareLength() const;

  Naive_EXPORT static const Vec3d &XAxis();

  Naive_EXPORT static const Vec3d &YAxis();

  Naive_EXPORT static const Vec3d &ZAxis();

  Naive_EXPORT static const Vec3d &Zero();

  Naive_EXPORT static const Vec3d &Unset();

  Naive_EXPORT Naive_Bool Normalize();

  Naive_EXPORT Vec3d Normalized() const;

  Naive_EXPORT void Add(const Vec3d &theVec);

  Naive_EXPORT Vec3d Added(const Vec3d &theVec) const;

  Naive_EXPORT void Subtract(const Vec3d &theVec);

  Naive_EXPORT Vec3d Subtracted(const Vec3d &theVec) const;

  Naive_EXPORT void Multiply(const Naive_Real theT);

  Naive_EXPORT Vec3d Multiplied(const Naive_Real theT) const;

  Naive_EXPORT Naive_Bool Divide(const Naive_Real theT);

  Naive_EXPORT Vec3d Divided(const Naive_Real theT) const;

  Naive_EXPORT void Negate();

  Naive_EXPORT Vec3d Negated() const;

  Naive_EXPORT Naive_Real Dot(const Vec3d &theVec) const;

  Naive_EXPORT void Cross(const Vec3d &theVec);

  Naive_EXPORT Vec3d Crossed(const Vec3d &theVec) const;

  Naive_EXPORT void Reverse();

  Naive_EXPORT Naive_Bool EpsilonEquals(
      const Vec3d &theVec, const Naive_Real theE = math::Precision::Epsilon0());

  Naive_EXPORT Naive_Bool Equals(const Vec3d &theVec);

  Naive_EXPORT Naive_Bool Transform(const Trsf3d &theTrsf);

  Naive_EXPORT Vec3d Transformed(const Trsf3d &theTrsf) const;

  Naive_EXPORT Naive_XYZW HomoCoord() const;

  Naive_EXPORT Naive_Bool Dump(Naive_Vector3d_t &theVec) const;

private:
  Naive_XYZ myXYZ;
};

Naive_EXPORT const Vec3d operator+(const Vec3d &theVec1, const Vec3d &theVec2);

Naive_EXPORT const Vec3d operator-(const Vec3d &theVec1, const Vec3d &theVec2);

Naive_EXPORT const Vec3d operator-(const Vec3d &theVec);

Naive_EXPORT const Vec3d operator*(const Vec3d &theVec, const Naive_Real theT);

Naive_EXPORT const Vec3d operator*(const Naive_Real theT, const Vec3d &theVec);

Naive_EXPORT const Naive_Real operator*(const Vec3d theVec1,
                                        const Vec3d &theVec2);

Naive_EXPORT const Vec3d operator/(const Vec3d &theVec, const Naive_Real theT);

Naive_NAMESPACE_END(math);

using Naive_Vec3d = ::naivecgl::math::Vec3d;
using Naive_Vec3dList1 = Naive_List1<Naive_Vec3d>;
using Naive_Vec3dList2 = Naive_List2<Naive_Vec3d>;

#endif
