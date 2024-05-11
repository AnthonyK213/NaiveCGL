#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Geometry/Transform3d.h>
#include <naivecgl/Geometry/Vector3d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Point3d::Point3d()
    : myXYZ(math::Constant::UnsetReal(), math::Constant::UnsetReal(),
            math::Constant::UnsetReal()) {}

Point3d::Point3d(const Naive_Real theX, const Naive_Real theY,
                 const Naive_Real theZ)
    : myXYZ(theX, theY, theZ) {}

Point3d::Point3d(const Naive_XYZ &theXYZ) : myXYZ(theXYZ) {}

Point3d::Point3d(const Naive_Point3d_T &thePnt)
    : myXYZ(thePnt.x, thePnt.y, thePnt.z) {}

const Point3d &Point3d::Origin() {
  static Point3d aPoint{0., 0., 0.};
  return aPoint;
}

const Point3d &Point3d::Unset() {
  static Point3d aPoint{};
  return aPoint;
}

void Point3d::SetXYZ(const Naive_Real theX, const Naive_Real theY,
                     const Naive_Real theZ) {
  SetX(theX);
  SetY(theY);
  SetZ(theZ);
}

Naive_Bool Point3d::IsValid() const {
  return math::Util::IsValidReal(myXYZ.x()) &&
         math::Util::IsValidReal(myXYZ.y()) &&
         math::Util::IsValidReal(myXYZ.z());
}

Naive_Real Point3d::DistanceTo(const Point3d &thePoint) const {
  if (!IsValid() || !thePoint.IsValid())
    return math::Constant::UnsetReal();
  return (myXYZ - thePoint.myXYZ).norm();
}

Naive_Real Point3d::DistanceToSquared(const Point3d &thePoint) const {
  if (!IsValid() || !thePoint.IsValid())
    return math::Constant::UnsetReal();
  return (myXYZ - thePoint.myXYZ).squaredNorm();
}

Naive_Bool Point3d::Add(const Point3d &thePoint) {
  if (IsValid() && thePoint.IsValid()) {
    myXYZ += thePoint.XYZ();
    return true;
  }
  return false;
}

Point3d Point3d::Added(const Point3d &thePoint) const {
  Point3d aPnt(*this);
  return aPnt.Add(thePoint) ? aPnt : Unset();
}

Naive_Bool Point3d::Add(const Vector3d &theVector) {
  if (IsValid() && theVector.IsValid()) {
    myXYZ += theVector.XYZ();
    return true;
  }
  return false;
}

Point3d Point3d::Added(const Vector3d &theVector) const {
  Point3d aPnt(*this);
  return aPnt.Add(theVector) ? aPnt : Unset();
}

Vector3d Point3d::Subtracted(const Point3d &thePoint) const {
  if (IsValid() && thePoint.IsValid())
    return {myXYZ - thePoint.XYZ()};
  return Vector3d::Unset();
}

Naive_Bool Point3d::Multiply(const Naive_Real &theT) {
  if (IsValid() && math::Util::IsValidReal(theT)) {
    myXYZ *= theT;
    return true;
  }
  return false;
}

Point3d Point3d::Multiplied(const Naive_Real &theT) const {
  Point3d aPnt(*this);
  return aPnt.Multiply(theT) ? aPnt : Unset();
}

Naive_Bool Point3d::Divide(const Naive_Real &theT) {
  if (IsValid() && math::Util::IsValidReal(theT) &&
      !math::Util::EpsilonEquals(theT, 0.0)) {
    myXYZ *= theT;
    return true;
  }
  return false;
}

Point3d Point3d::Divided(const Naive_Real &theT) const {
  Point3d aPnt(*this);
  return aPnt.Divide(theT) ? aPnt : Unset();
}

void Point3d::Negate() { myXYZ = -myXYZ; }

Point3d Point3d::Negated() const { return {-myXYZ}; }

Naive_Bool Point3d::Transform(const Transform3d &theTrsf) {
  if (!IsValid() || !theTrsf.IsValid())
    return false;
  myXYZ = theTrsf.Trsf() * myXYZ;
  return true;
}

Point3d Point3d::Transformed(const Transform3d &theTrsf) const {
  Point3d aPnt(*this);
  return aPnt.Transform(theTrsf) ? aPnt : Unset();
}

Naive_Integer Point3d::CompareTo(const Point3d &thePoint) const {
  if (X() < thePoint.X())
    return -1;
  if (X() > thePoint.X())
    return 1;
  if (Y() < thePoint.Y())
    return -1;
  if (Y() > thePoint.Y())
    return 1;
  if (Z() < thePoint.Z())
    return -1;
  if (Z() > thePoint.Z())
    return 1;
  return 0;
}

Naive_Bool Point3d::Dump(Naive_Point3d_T &theP) const {
  if (!IsValid())
    return false;
  theP.x = X();
  theP.y = Y();
  theP.z = Z();
  return true;
}

const Point3d operator+(const Point3d &thePnt1, const Point3d &thePnt2) {
  return thePnt1.Added(thePnt2);
}

const Point3d operator+(const Point3d &thePnt, const Vector3d &theVec) {
  return thePnt.Added(theVec);
}

const Vector3d operator-(const Point3d &thePnt1, const Point3d &thePnt2) {
  return thePnt1.Subtracted(thePnt2);
}

const Point3d operator-(const Point3d &thePnt) { return thePnt.Negated(); }

const Point3d operator*(const Point3d &thePnt, const Naive_Real theT) {
  return thePnt.Multiplied(theT);
}

const Point3d operator*(const Naive_Real theT, const Point3d &thePnt) {
  return thePnt.Multiplied(theT);
}

const Point3d operator/(const Point3d &thePnt, const Naive_Real theT) {
  return thePnt.Divided(theT);
}

Naive_NAMESPACE_END(geometry);
