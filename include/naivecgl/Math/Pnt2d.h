#ifndef _NaiveCGL_Math_Pnt2d_HeaderFile
#define _NaiveCGL_Math_Pnt2d_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(math);

class Pnt2d final {
public:
  Naive_EXPORT Pnt2d();

  Naive_EXPORT Pnt2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Pnt2d(const Naive_Point2d_t &thePnt);

  Naive_EXPORT Pnt2d(const Naive_XY &theXY);

  Naive_EXPORT const Naive_XY &XY() const { return myXY; }

  Naive_EXPORT Naive_XY &ChangeXY() { return myXY; }

  Naive_EXPORT Naive_Real X() const { return myXY.x(); }

  Naive_EXPORT Naive_Real Y() const { return myXY.y(); }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Real DistanceTo(const Pnt2d &theP) const;

  Naive_EXPORT Naive_Real DistanceToSquared(const Pnt2d &theP) const;

  Naive_EXPORT Naive_XYZ HomoCoord() const;

  Naive_EXPORT Naive_Bool HomoCoord(const Naive_XYZ &theXYZ);

  Naive_EXPORT static const Pnt2d &Unset();

  Naive_EXPORT Naive_Bool Dump(Naive_Point2d_t &theP) const;

private:
  Naive_XY myXY;
};

Naive_NAMESPACE_END(math);

using Naive_Pnt2d = ::naivecgl::math::Pnt2d;
using Naive_Pnt2dList1 = Naive_List1<Naive_Pnt2d>;
using Naive_Pnt2dList2 = Naive_List2<Naive_Pnt2d>;

#endif
