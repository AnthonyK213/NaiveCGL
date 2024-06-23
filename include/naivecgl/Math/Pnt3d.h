#ifndef _NaiveCGL_Math_Pnt3d_HeaderFile
#define _NaiveCGL_Math_Pnt3d_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(math);

class Vec3d;
class Trsf3d;

class Pnt3d final {
public:
  Naive_EXPORT Pnt3d();

  Naive_EXPORT Pnt3d(const Naive_Real theX, const Naive_Real theY,
                     const Naive_Real theZ);

  Naive_EXPORT Pnt3d(const Naive_XYZ &theXYZ);

  Naive_EXPORT Pnt3d(const Naive_Point3d_t &thePnt);

  Naive_EXPORT static const Pnt3d &Origin();

  Naive_EXPORT static const Pnt3d &Unset();

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

  Naive_EXPORT Naive_Real DistanceTo(const Pnt3d &thePoint) const;

  Naive_EXPORT Naive_Real DistanceToSquared(const Pnt3d &thePoint) const;

  Naive_EXPORT Naive_Bool Add(const Pnt3d &thePoint);

  Naive_EXPORT Pnt3d Added(const Pnt3d &thePoint) const;

  Naive_EXPORT Naive_Bool Add(const Vec3d &theVector);

  Naive_EXPORT Pnt3d Added(const Vec3d &theVector) const;

  Naive_EXPORT Vec3d Subtracted(const Pnt3d &thePoint) const;

  Naive_EXPORT Naive_Bool Multiply(const Naive_Real &theT);

  Naive_EXPORT Pnt3d Multiplied(const Naive_Real &theT) const;

  Naive_EXPORT Naive_Bool Divide(const Naive_Real &theT);

  Naive_EXPORT Pnt3d Divided(const Naive_Real &theT) const;

  Naive_EXPORT void Negate();

  Naive_EXPORT Pnt3d Negated() const;

  Naive_EXPORT Naive_Bool Transform(const Trsf3d &theTrsf);

  Naive_EXPORT Pnt3d Transformed(const Trsf3d &theTrsf) const;

  Naive_EXPORT Naive_Integer CompareTo(const Pnt3d &thePoint) const;

  Naive_EXPORT Naive_Bool Dump(Naive_Point3d_t &theP) const;

private:
  Naive_XYZ myXYZ;
};

Naive_EXPORT const Pnt3d operator+(const Pnt3d &thePnt1, const Pnt3d &thePnt2);

Naive_EXPORT const Pnt3d operator+(const Pnt3d &thePnt, const Vec3d &theVec);

Naive_EXPORT const Vec3d operator-(const Pnt3d &thePnt1, const Pnt3d &thePnt2);

Naive_EXPORT const Pnt3d operator-(const Pnt3d &thePnt);

Naive_EXPORT const Pnt3d operator*(const Pnt3d &thePnt, const Naive_Real theT);

Naive_EXPORT const Pnt3d operator*(const Naive_Real theT, const Pnt3d &thePnt);

Naive_EXPORT const Pnt3d operator/(const Pnt3d &thePnt, const Naive_Real theT);

Naive_NAMESPACE_END(math);

using Naive_Pnt3d = ::naivecgl::math::Pnt3d;
using Naive_Pnt3dList1 = Naive_List1<Naive_Pnt3d>;
using Naive_Pnt3dList2 = Naive_List2<Naive_Pnt3d>;

#endif
