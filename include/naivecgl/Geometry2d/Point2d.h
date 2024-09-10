#ifndef _NaiveCGL_Geometry2d_Point2d_HeaderFile
#define _NaiveCGL_Geometry2d_Point2d_HeaderFile

#include "../Math/Pnt2d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Point2d : public Naive_Geometry2d {
public:
  Naive_EXPORT virtual Naive_Pnt2d Pnt2d() const = 0;

  Naive_EXPORT virtual Naive_Real X() const = 0;

  Naive_EXPORT virtual Naive_Real Y() const = 0;

  Naive_EXPORT Naive_Real DistanceTo(const Naive_Handle<Point2d> &theP) const;

  Naive_EXPORT Naive_Real
  DistanceToSquared(const Naive_Handle<Point2d> &theP) const;

  Naive_DEFINE_RTTI(Point2d, Naive_Geometry2d);
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Point2d = ::naivecgl::geometry2d::Point2d;
Naive_DEFINE_HANDLE(Naive_Point2d);
using Naive_Point2dList1 = Naive_List1<Handle_Naive_Point2d>;
using Naive_Point2dList2 = Naive_List2<Handle_Naive_Point2d>;

#endif
