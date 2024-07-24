#include <naivecgl/Math/Ax22d.h>

Naive_NAMESPACE_BEGIN(math);

Ax22d::Ax22d() : myLoc(), myXDir(), myYDir() {}

Ax22d::Ax22d(const Naive_Pnt2d &theP, const Naive_Vec2d &theVx,
             const Naive_Vec2d &theVy)
    : myLoc(theP), myXDir(theVx.Normalized()), myYDir(theVy.Normalized()) {
  Naive_Real aValue = myXDir.Crossed(myYDir);
  if (aValue >= 0.0) {
    myYDir.SetCoord(-myXDir.Y(), myXDir.X());
  } else {
    myYDir.SetCoord(myXDir.Y(), -myXDir.X());
  };
}

Ax22d::Ax22d(const Naive_Pnt2d &theP, const Naive_Vec2d &theV,
             const Naive_Bool &theIsSense)
    : myLoc(theP), myXDir(theV) {
  if (theIsSense) {
    myYDir.SetCoord(-myXDir.Y(), myXDir.X());
  } else {
    myYDir.SetCoord(myXDir.Y(), -myXDir.X());
  }
}

void Ax22d::SetXDirection(const Naive_Vec2d &theV) { Naive_TODO; }

void Ax22d::SetYDirection(const Naive_Vec2d &theV) { Naive_TODO; }

Naive_Bool Ax22d::IsValid() const {
  return myLoc.IsValid() && myXDir.IsValid() && myYDir.IsValid();
}

Naive_Bool Ax22d ::Dump(Naive_Ax22d_sf_t &theAx22d) const {
  return myLoc.Dump(theAx22d.location) && myXDir.Dump(theAx22d.x_axis) &&
         myYDir.Dump(theAx22d.y_axis);
}

Naive_NAMESPACE_END(math);
