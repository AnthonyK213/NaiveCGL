#ifndef _NaiveCGL_Geometry_Point2d_HeaderFile
#define _NaiveCGL_Geometry_Point2d_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(geometry);

class Point2d final {
public:
  Naive_EXPORT Point2d();

  Naive_EXPORT Point2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Point2d(const Naive_Point2d_t &thePoint);

  Naive_EXPORT Point2d(const Naive_XY &theXY);

  Naive_EXPORT const Naive_XY &XY() const { return myXY; }

  Naive_EXPORT Naive_XY &ChangeXY() { return myXY; }

  Naive_EXPORT Naive_Real X() const { return myXY.x(); }

  Naive_EXPORT Naive_Real Y() const { return myXY.y(); }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Real DistanceTo(const Point2d &theP) const;

  Naive_EXPORT Naive_Real DistanceToSquared(const Point2d &theP) const;

  Naive_EXPORT static const Point2d &Unset();

  Naive_EXPORT Naive_Bool Dump(Naive_Point2d_t &theP) const;

private:
  Naive_XY myXY;
};

Naive_NAMESPACE_END(geometry);

using Naive_Point2d = ::naivecgl::geometry::Point2d;
using Naive_Point2dList = Naive_List<Naive_Point2d>;
using Naive_Point2dList2 = Naive_List2<Naive_Point2d>;

#endif
