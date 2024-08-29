#ifndef _NaiveCGL_Math_Pnt2d_HeaderFile
#define _NaiveCGL_Math_Pnt2d_HeaderFile

#include "../Collection/List1.h"
#include "../Collection/List2.h"
#include "../Common/Macro.h"
#include "../Common/Type.h"
#include "XY.h"
#include "XYZ.h"

Naive_NAMESPACE_BEGIN(math);

class Vec2d;

class Pnt2d final {
public:
  Naive_EXPORT Pnt2d();

  Naive_EXPORT Pnt2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Pnt2d(const Naive_Pnt2d_t &thePnt);

  Naive_EXPORT Pnt2d(const Naive_XY &theXY);

  const Naive_XY &XY() const { return myXY; }

  Naive_XY &ChangeXY() { return myXY; }

  Naive_Real X() const { return myXY.x(); }

  Naive_Real Y() const { return myXY.y(); }

  void SetX(Naive_Real theVal) { myXY.x() = theVal; }

  void SetY(Naive_Real theVal) { myXY.y() = theVal; }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Real DistanceTo(const Pnt2d &theP) const;

  Naive_EXPORT Naive_Real DistanceToSquared(const Pnt2d &theP) const;

  Naive_EXPORT void Add(const Pnt2d &thePoint);

  Naive_EXPORT Pnt2d Added(const Pnt2d &thePoint) const;

  Naive_EXPORT void Add(const Vec2d &theVector);

  Naive_EXPORT Pnt2d Added(const Vec2d &theVector) const;

  Naive_EXPORT Vec2d Subtracted(const Pnt2d &thePoint) const;

  Naive_EXPORT void Multiply(const Naive_Real &theT);

  Naive_EXPORT Pnt2d Multiplied(const Naive_Real &theT) const;

  Naive_EXPORT Naive_Bool Divide(const Naive_Real &theT);

  Naive_EXPORT Pnt2d Divided(const Naive_Real &theT) const;

  Naive_EXPORT void Negate();

  Naive_EXPORT Pnt2d Negated() const;

  Naive_EXPORT Naive_XYZ HomoCoord() const;

  Naive_EXPORT Naive_Bool HomoCoord(const Naive_XYZ &theXYZ);

  Naive_EXPORT static const Pnt2d &Unset();

  Naive_EXPORT Naive_Bool Dump(Naive_Pnt2d_t &theP) const;

private:
  Naive_XY myXY;
};

Naive_NAMESPACE_END(math);

using Naive_Pnt2d = ::naivecgl::math::Pnt2d;
using Naive_Pnt2dList1 = Naive_List1<Naive_Pnt2d>;
using Naive_Pnt2dList2 = Naive_List2<Naive_Pnt2d>;

#endif
