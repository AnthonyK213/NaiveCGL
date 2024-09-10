#ifndef _NaiveCGL_Geometry_Point3d_HeaderFile
#define _NaiveCGL_Geometry_Point3d_HeaderFile

#include "../Math/Pnt3d.h"
#include "../Math/Trsf3d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry);

class Point3d : public Naive_Geometry {
public:
  Naive_EXPORT virtual Naive_Pnt3d Pnt() const = 0;

  Naive_EXPORT virtual Naive_Real X() const = 0;

  Naive_EXPORT virtual Naive_Real Y() const = 0;

  Naive_EXPORT virtual Naive_Real Z() const = 0;

  Naive_EXPORT Naive_Real DistanceTo(const Naive_Handle<Point3d> &theP) const;

  Naive_EXPORT Naive_Real
  DistanceToSquared(const Naive_Handle<Point3d> &theP) const;

  Naive_EXPORT virtual Naive_Code Dump(Naive_Point_sf_t &theSF) const;

  Naive_DEFINE_RTTI(Point3d, Naive_Geometry);
};

Naive_NAMESPACE_END(geometry);

using Naive_Point3d = ::naivecgl::geometry::Point3d;
Naive_DEFINE_HANDLE(Naive_Point3d);
using Naive_Point3dList1 = Naive_List1<Handle_Naive_Point3d>;
using Naive_Point3dList2 = Naive_List2<Handle_Naive_Point3d>;

#endif
