#ifndef _NaiveCGL_Geometry2d_Point2d_HeaderFile
#define _NaiveCGL_Geometry2d_Point2d_HeaderFile

#include "../Math/Pnt2d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Point2d final : public Naive_Geometry2d {
public:
  Naive_EXPORT Point2d();

  Naive_EXPORT Point2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Point2d(const Naive_Pnt2d &thePnt2d);

  Naive_EXPORT const Naive_Pnt2d &Pnt2d() const { return myPnt2d; }

  Naive_EXPORT Naive_Real X() const { return myPnt2d.X(); }

  Naive_EXPORT Naive_Real Y() const { return myPnt2d.Y(); }

  Naive_EXPORT Naive_Real DistanceTo(const Naive_Handle<Point2d> &theP) const;

  Naive_EXPORT Naive_Real
  DistanceToSquared(const Naive_Handle<Point2d> &theP) const;

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry2d Clone() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Point2d, Naive_Geometry2d, Naive_Class_point2d);

private:
  Naive_Pnt2d myPnt2d;
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Point2d = ::naivecgl::geometry2d::Point2d;
Naive_DEFINE_HANDLE(Naive_Point2d);
using Naive_Point2dList1 = Naive_List1<Handle_Naive_Point2d>;
using Naive_Point2dList2 = Naive_List2<Handle_Naive_Point2d>;

#endif
