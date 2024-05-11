#include <naivecgl/Geometry/Box.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Box::Box() : myMin(1.0, 0.0, 0.0), myMax(-1.0, 0.0, 0.0) {}

Box::Box(const Naive_Point3d &theMin, const Naive_Point3d &theMax)
    : myMin(theMin), myMax(theMax) {}

const Box &Box::Unset() {
  static Box aBox(Naive_Point3d::Unset(), Naive_Point3d::Unset());
  return aBox;
}

const Box &Box::Void() {
  static Box aBox{};
  return aBox;
}

Naive_Bool Box::IsValid() const { return isSet() && isValid(); }

Naive_Bool Box::IsVoid() const { return isSet() && isVoid(); }

Naive_Bool Box::IsPoint() const { return isSet() && isPoint(); }

void Box::Update(const Naive_Real theXMin, const Naive_Real theYMin,
                 const Naive_Real theZMin, const Naive_Real theXMax,
                 const Naive_Real theYMax, const Naive_Real theZMax) {
  if (!isSet())
    return;

  if (isVoid()) {
    myMin.SetXYZ(theXMin, theYMin, theZMin);
    myMax.SetXYZ(theXMax, theYMax, theZMax);
  } else {
    if (theXMin < myMin.X())
      myMin.SetX(theXMin);
    if (theYMin < myMin.Y())
      myMin.SetY(theYMin);
    if (theZMin < myMin.Z())
      myMin.SetZ(theZMin);
    if (theXMax > myMax.X())
      myMax.SetX(theXMax);
    if (theYMax > myMax.Y())
      myMax.SetY(theYMax);
    if (theZMax > myMax.Z())
      myMax.SetZ(theZMax);
  }
}

void Box::Update(const Naive_Real theX, const Naive_Real theY,
                 const Naive_Real theZ) {
  if (!isSet())
    return;

  if (isVoid()) {
    myMin.SetXYZ(theX, theY, theZ);
    myMax.SetXYZ(theX, theY, theZ);
  } else {
    if (theX < myMin.X())
      myMin.SetX(theX);
    else if (theX > myMax.X())
      myMax.SetX(theX);

    if (theY < myMin.Y())
      myMin.SetY(theY);
    else if (theY > myMax.Y())
      myMax.SetY(theY);

    if (theZ < myMin.Z())
      myMin.SetZ(theZ);
    else if (theZ > myMax.Z())
      myMax.SetZ(theZ);
  }
}

void Box::Add(const Box &theOther) {
  if (!isSet() || !theOther.isSet())
    return;

  if (theOther.isVoid()) {
    return;
  } else if (isVoid()) {
    *this = theOther;
    return;
  }

  if (myMin.X() > theOther.Min().X())
    myMin.SetX(theOther.Min().X());
  if (myMax.X() < theOther.Max().X())
    myMax.SetX(theOther.Max().X());
  if (myMin.Y() > theOther.Min().Y())
    myMin.SetY(theOther.Min().Y());
  if (myMax.Y() < theOther.Max().Y())
    myMax.SetY(theOther.Max().Y());
  if (myMin.Z() > theOther.Min().Z())
    myMin.SetZ(theOther.Min().Z());
  if (myMax.Z() < theOther.Max().Z())
    myMax.SetZ(theOther.Max().Z());
}

void Box::Add(const Naive_Point3d &thePoint) {
  Update(thePoint.X(), thePoint.Y(), thePoint.Z());
}

Naive_Bool Box::isSet() const { return myMin.IsValid() && myMax.IsValid(); }

Naive_Bool Box::isValid() const {
  return myMin.X() <= myMax.X() && myMin.Y() <= myMax.Y() &&
         myMin.Z() <= myMax.Z();
}

Naive_Bool Box::isVoid() const {
  return myMin.X() > myMax.X() || myMin.Y() > myMax.Y() ||
         myMin.Z() > myMax.Z();
}

Naive_Bool Box::isPoint() const {
  return myMin.X() == myMax.X() && myMin.Y() == myMax.Y() &&
         myMin.Z() == myMax.Z();
}

Naive_NAMESPACE_END(geometry);
