#include <naivecgl/Geometry/Box.h>
#include <naivecgl/Geometry/Interval.h>
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

Naive_Point3d Box::Corner(Naive_Bool theMinX, Naive_Bool theMinY,
                          Naive_Bool theMinZ) const {
  if (!isValid())
    return Naive_Point3d::Unset();

  Naive_Point3d aPnt{};
  aPnt.SetX((theMinX ? myMin : myMax).X());
  aPnt.SetY((theMinX ? myMin : myMax).Y());
  aPnt.SetZ((theMinX ? myMin : myMax).Z());

  return aPnt;
}

Naive_EXPORT Naive_Point3dList Box::Corners() const {
  if (!isValid())
    return Naive_Point3dList(8, Naive_Point3d::Unset());

  Naive_Point3dList aRes(8);
  aRes[0].SetXYZ(myMin.X(), myMin.Y(), myMin.Z());
  aRes[1].SetXYZ(myMax.X(), myMin.Y(), myMin.Z());
  aRes[2].SetXYZ(myMax.X(), myMax.Y(), myMin.Z());
  aRes[3].SetXYZ(myMin.X(), myMax.Y(), myMin.Z());
  aRes[4].SetXYZ(myMin.X(), myMin.Y(), myMax.Z());
  aRes[5].SetXYZ(myMax.X(), myMin.Y(), myMax.Z());
  aRes[6].SetXYZ(myMax.X(), myMax.Y(), myMax.Z());
  aRes[7].SetXYZ(myMin.X(), myMax.Y(), myMax.Z());

  return aRes;
}

Naive_Bool Box::Contains(const Box &theBox) const {
  return (IsValid() && theBox.IsValid()) && theBox.myMin.X() >= myMin.X() &&
         theBox.myMax.X() <= myMax.X() && theBox.myMin.Y() >= myMin.Y() &&
         theBox.myMax.Y() <= myMax.Y() && theBox.myMin.Z() >= myMin.Z() &&
         theBox.myMax.Z() <= myMax.Z();
}

Naive_Bool Box::Contains(const Box &theBox, const Naive_Bool theStrict) const {
  if (theStrict) {
    return (IsValid() && theBox.IsValid()) && theBox.myMin.X() > myMin.X() &&
           theBox.myMax.X() < myMax.X() && theBox.myMin.Y() > myMin.Y() &&
           theBox.myMax.Y() < myMax.Y() && theBox.myMin.Z() > myMin.Z() &&
           theBox.myMax.Z() < myMax.Z();
  } else {
    return Contains(theBox);
  }
}

Naive_Bool Box::Contains(const Naive_Point3d &thePoint) const {
  return (IsValid() && thePoint.IsValid()) && thePoint.X() >= myMin.X() &&
         thePoint.X() <= myMax.X() && thePoint.Y() >= myMin.Y() &&
         thePoint.Y() <= myMax.Y() && thePoint.Z() >= myMin.Z() &&
         thePoint.Z() <= myMax.Z();
}

Naive_Bool Box::Contains(const Naive_Point3d &thePoint,
                         const Naive_Bool theStrict) const {
  if (theStrict) {
    return (IsValid() && thePoint.IsValid()) && thePoint.X() > myMin.X() &&
           thePoint.X() < myMax.X() && thePoint.Y() > myMin.Y() &&
           thePoint.Y() < myMax.Y() && thePoint.Z() > myMin.Z() &&
           thePoint.Z() < myMax.Z();
  } else {
    return Contains(thePoint);
  }
}

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

Naive_Point3d Box::PointAt(const Naive_Real theTx, const Naive_Real theTy,
                           const Naive_Real theTz) const {
  if (!IsValid())
    return Naive_Point3d::Unset();

  static Naive_Interval aInt(0.0, 1.0);
  if (!aInt.IncludesParameter(theTx) || !aInt.IncludesParameter(theTy) ||
      !aInt.IncludesParameter(theTz))
    return Naive_Point3d::Unset();

  Naive_Point3d aPnt{};
  aPnt.SetX((1.0 - theTx) * myMin.X() + theTx * myMax.X());
  aPnt.SetY((1.0 - theTy) * myMin.Y() + theTx * myMax.Y());
  aPnt.SetZ((1.0 - theTz) * myMin.Z() + theTx * myMax.Z());
  return aPnt;
}

Naive_Bool Box::Transform(const Naive_Transform3d &theTrsf) {
  if (!IsValid() || theTrsf.IsValid())
    return false;

  if (theTrsf.IsIdentity())
    return true;

  Naive_Point3dList aCorners = Corners();
  myMin.SetXYZ(1.0, 0.0, 0.0);
  myMax.SetXYZ(-1.0, 0.0, 0.0);
  for (auto &aCorner : aCorners) {
    aCorner.Transform(theTrsf);
    Add(aCorner);
  }

  return true;
}

Box Box::Transformed(const Naive_Transform3d &theTrsf) const {
  Box aBox(*this);
  return aBox.Transform(theTrsf) ? aBox : Unset();
}

Box Box::Intersection(const Box theA, const Box theB) {
  if (!theA.IsValid() || !theB.IsValid())
    return Unset();

  Box aBox{};
  aBox.myMin.SetX((::std::max)(theA.Min().X(), theB.Min().X()));
  aBox.myMax.SetX((::std::min)(theA.Max().X(), theB.Max().X()));
  aBox.myMin.SetY((::std::max)(theA.Min().Y(), theB.Min().Y()));
  aBox.myMax.SetY((::std::min)(theA.Max().Y(), theB.Max().Y()));
  aBox.myMin.SetZ((::std::max)(theA.Min().Z(), theB.Min().Z()));
  aBox.myMax.SetZ((::std::min)(theA.Max().Z(), theB.Max().Z()));
  return aBox;
}

Box Box::Union(const Box theA, const Box theB) {
  Box aBox(theA);
  aBox.Add(theB);
  return aBox;
}

Box Box::Union(const Box theBox, const Naive_Point3d &thePnt) {
  Box aBox(theBox);
  aBox.Add(thePnt);
  return aBox;
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
