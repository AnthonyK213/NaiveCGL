#ifndef _NaiveCGL_Math_Vec2d_HeaderFile
#define _NaiveCGL_Math_Vec2d_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(math);

class Vec2d final {
public:
  Naive_EXPORT Vec2d();

  Naive_EXPORT Vec2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Vec2d(const Naive_Vector2d_t &theVec);

  Naive_EXPORT Vec2d(const Naive_XY &theXY);

  const Naive_XY &XY() const { return myXY; }

  Naive_XY &ChangeXY() { return myXY; }

  Naive_Real X() const { return myXY.x(); }

  Naive_Real Y() const { return myXY.y(); }

  void SetX(const Naive_Real theX) { myXY.x() = theX; }

  void SetY(const Naive_Real theY) { myXY.y() = theY; }

  void SetCoord(const Naive_Real theX, const Naive_Real theY) {
    myXY.x() = theX;
    myXY.y() = theY;
  }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool IsZero() const;

  Naive_EXPORT Naive_Bool Normalize();

  Naive_EXPORT Vec2d Normalized() const;

  Naive_EXPORT Naive_Real Dot(const Vec2d &theV) const;

  Naive_EXPORT Naive_Real Crossed(const Vec2d &theV) const;

  Naive_EXPORT static const Vec2d &Unset();

  Naive_EXPORT Naive_Bool Dump(Naive_Vector2d_t &theV) const;

private:
  Naive_XY myXY;
};

Naive_NAMESPACE_END(math);

using Naive_Vec2d = ::naivecgl::math::Vec2d;
using Naive_Vec2dList1 = Naive_List1<Naive_Vec2d>;
using Naive_Vec2dList2 = Naive_List2<Naive_Vec2d>;

#endif
