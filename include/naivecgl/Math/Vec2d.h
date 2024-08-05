#ifndef _NaiveCGL_Math_Vec2d_HeaderFile
#define _NaiveCGL_Math_Vec2d_HeaderFile

#include "../Collection/List1.h"
#include "../Collection/List2.h"
#include "../Common/Macro.h"
#include "../Common/Type.h"
#include "XY.h"
#include "XYZ.h"

Naive_NAMESPACE_BEGIN(math);

class Vec2d final {
public:
  Naive_EXPORT Vec2d();

  Naive_EXPORT Vec2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Vec2d(const Naive_Vec2d_t &theVec);

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

  Naive_EXPORT Naive_Real Length() const;

  Naive_EXPORT Naive_Real SquareLength() const;

  Naive_EXPORT static const Vec2d &XAxis();

  Naive_EXPORT static const Vec2d &YAxis();

  Naive_EXPORT static const Vec2d &Zero();

  Naive_EXPORT static const Vec2d &Unset();

  Naive_EXPORT Naive_Bool Normalize();

  Naive_EXPORT Vec2d Normalized() const;

  Naive_EXPORT void Add(const Vec2d &theVec);

  Naive_EXPORT Vec2d Added(const Vec2d &theVec) const;

  Naive_EXPORT void Subtract(const Vec2d &theVec);

  Naive_EXPORT Vec2d Subtracted(const Vec2d &theVec) const;

  Naive_EXPORT void Multiply(const Naive_Real theT);

  Naive_EXPORT Vec2d Multiplied(const Naive_Real theT) const;

  Naive_EXPORT Naive_Bool Divide(const Naive_Real theT);

  Naive_EXPORT Vec2d Divided(const Naive_Real theT) const;

  Naive_EXPORT Naive_Real Dot(const Vec2d &theV) const;

  Naive_EXPORT Naive_Real Crossed(const Vec2d &theV) const;

  Naive_EXPORT Naive_XYZ HomoCoord() const;

  Naive_EXPORT Naive_Bool Dump(Naive_Vec2d_t &theV) const;

private:
  Naive_XY myXY;
};

Naive_NAMESPACE_END(math);

using Naive_Vec2d = ::naivecgl::math::Vec2d;
using Naive_Vec2dList1 = Naive_List1<Naive_Vec2d>;
using Naive_Vec2dList2 = Naive_List2<Naive_Vec2d>;

#endif
