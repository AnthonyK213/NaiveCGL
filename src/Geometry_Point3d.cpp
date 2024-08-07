﻿#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Point3d);

Point3d::Point3d() : myPnt() {}

Point3d::Point3d(const Naive_Real theX, const Naive_Real theY,
                 const Naive_Real theZ)
    : myPnt(theX, theY, theZ) {}

Point3d::Point3d(const Naive_Pnt3d &thePnt) : myPnt(thePnt) {}

Naive_Real Point3d::DistanceTo(const Handle_Naive_Point3d &theP) const {
  if (theP.IsNull())
    return math::Constant::UnsetReal();
  return myPnt.DistanceTo(theP->myPnt);
}

Naive_Real Point3d::DistanceToSquared(const Handle_Naive_Point3d &theP) const {
  if (theP.IsNull())
    return math::Constant::UnsetReal();
  return myPnt.DistanceToSquared(theP->myPnt);
}

void Point3d::Transform(const Naive_Trsf3d &theTrsf) {
  myPnt.Transform(theTrsf);
}

Naive_Bool Point3d::IsValid() const { return myPnt.IsValid(); }

Handle_Naive_Geometry Point3d::Clone() const { return new Point3d(myPnt); }

Naive_NAMESPACE_END(geometry);
