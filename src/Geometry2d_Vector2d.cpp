#include <naivecgl/Geometry2d/Vector2d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry2d);

Naive_IMPLEMENT_RTTI(Vector2d);

Vector2d::Vector2d() : myVec2d() {}

Vector2d::Vector2d(const Naive_Real theX, const Naive_Real theY)
    : myVec2d(theX, theY) {}

Vector2d::Vector2d(const Naive_Vec2d &theVec2d) : myVec2d(theVec2d) {}

Naive_Bool Vector2d::IsValid() const { return myVec2d.IsValid(); }

Handle_Naive_Geometry2d Vector2d::Clone() const {
  return new Vector2d(myVec2d);
}

Naive_NAMESPACE_END(geometry2d);
