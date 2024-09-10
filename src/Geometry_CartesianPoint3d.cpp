#include <naivecgl/Geometry/CartesianPoint3d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Trsf3d.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(CartesianPoint3d);

CartesianPoint3d::CartesianPoint3d() : myPnt() {}

CartesianPoint3d::CartesianPoint3d(const Naive_Real theX, const Naive_Real theY,
                               const Naive_Real theZ)
    : myPnt(theX, theY, theZ) {}

CartesianPoint3d::CartesianPoint3d(const Naive_Pnt3d &thePnt) : myPnt(thePnt) {}

CartesianPoint3d::CartesianPoint3d(const Naive_Point_sf_t &theSF)
    : myPnt(theSF.position) {}

Naive_Bool CartesianPoint3d::IsValid() const { return myPnt.IsValid(); }

Handle_Naive_Geometry CartesianPoint3d::Clone() const {
  return new CartesianPoint3d(myPnt);
}

Naive_Code CartesianPoint3d::transform(const Naive_Trsf3d &theTrsf) {
  myPnt.Transform(theTrsf);
  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry);
