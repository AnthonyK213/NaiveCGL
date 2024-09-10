#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Trsf3d.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Point3d);

Naive_Real Point3d::DistanceTo(const Handle_Naive_Point3d &theP) const {
  return ::std::sqrt(DistanceToSquared(theP));
}

Naive_Real Point3d::DistanceToSquared(const Handle_Naive_Point3d &theP) const {
  Naive_Real dX = X() - theP->X();
  Naive_Real dY = Y() - theP->Y();
  Naive_Real dZ = Z() - theP->Z();
  return dX * dX + dY * dY + dZ * dZ;
}

Naive_Code Point3d::Dump(Naive_Point_sf_t &theSF) const {
  if (!Pnt().Dump(theSF.position))
    return Naive_Code_invalid_value;
  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry);
