#include <naivecgl/Geometry/Vector3d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(Vector3d);

Vector3d::Vector3d() : myVec() {}

Vector3d::Vector3d(const Naive_Pnt3d &theP1, const Naive_Pnt3d &theP2)
    : myVec(theP2 - theP1) {}

Vector3d::Vector3d(const Naive_Real theX, const Naive_Real theY,
                   const Naive_Real theZ)
    : myVec(theX, theY, theZ) {}

Vector3d::Vector3d(const Naive_Vec3d &theVec) : myVec(theVec) {}

Naive_Bool Vector3d::IsValid() const { return myVec.IsValid(); }

Handle_Naive_Geometry Vector3d::Clone() const { return new Vector3d(myVec); }

Naive_Real Vector3d::Length() const { return myVec.Length(); }

Naive_Real Vector3d::SquareLength() const { return myVec.SquareLength(); }

Naive_Bool Vector3d::Normalize() { return myVec.Normalize(); }

Naive_Handle<Vector3d> Vector3d::Normalized() const {
  return new Vector3d(myVec.Normalized());
}

void Vector3d::Add(const Naive_Handle<Vector3d> &theVec) {
  if (!theVec.IsNull())
    myVec.Add(theVec->myVec);
}

Naive_Handle<Vector3d>
Vector3d::Added(const Naive_Handle<Vector3d> &theVec) const {
  if (theVec.IsNull())
    return new Vector3d;
  return new Vector3d(myVec.Added(theVec->myVec));
}

void Vector3d::Subtract(const Naive_Handle<Vector3d> &theVec) {
  if (!theVec.IsNull())
    myVec.Subtract(theVec->myVec);
}

Naive_Handle<Vector3d>
Vector3d::Subtracted(const Naive_Handle<Vector3d> &theVec) const {
  if (theVec.IsNull())
    return new Vector3d;
  return new Vector3d(myVec.Subtracted(theVec->myVec));
}

void Vector3d::Multiply(const Naive_Real theT) { myVec.Multiply(theT); }

Naive_Handle<Vector3d> Vector3d::Multiplied(const Naive_Real theT) const {
  return new Vector3d(myVec.Multiplied(theT));
}

Naive_Bool Vector3d::Divide(const Naive_Real theT) {
  return myVec.Divide(theT);
}

Naive_Handle<Vector3d> Vector3d::Divided(const Naive_Real theT) const {
  return new Vector3d(myVec.Divided(theT));
}

Naive_Real Vector3d::Dot(const Naive_Handle<Vector3d> &theVec) const {
  if (theVec.IsNull())
    return math::Constant::UnsetReal();
  return myVec.Dot(theVec->myVec);
}

void Vector3d::Cross(const Naive_Handle<Vector3d> &theVec) {
  if (theVec.IsNull())
    return;
  myVec.Cross(theVec->myVec);
}

Naive_Handle<Vector3d>
Vector3d::Crossed(const Naive_Handle<Vector3d> &theVec) const {
  if (theVec.IsNull())
    return new Vector3d;
  return new Vector3d(myVec.Crossed(theVec->myVec));
}

void Vector3d::Reverse() { myVec.Reverse(); }

Naive_Handle<Vector3d> Vector3d::Reversed() const {
  return new Vector3d(myVec.Negated());
}

Naive_Bool Vector3d::Transform(const Naive_Trsf3d &theTrsf) {
  return myVec.Transform(theTrsf);
}

Naive_NAMESPACE_END(geometry);
