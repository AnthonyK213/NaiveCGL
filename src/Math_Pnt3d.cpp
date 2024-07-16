#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Pnt3d.h>
#include <naivecgl/Math/Trsf3d.h>
#include <naivecgl/Math/Util.h>
#include <naivecgl/Math/Vec3d.h>

Naive_NAMESPACE_BEGIN(math);

Pnt3d::Pnt3d()
    : myXYZ(Constant::UnsetReal(), Constant::UnsetReal(),
            Constant::UnsetReal()) {}

Pnt3d::Pnt3d(const Naive_Real theX, const Naive_Real theY,
             const Naive_Real theZ)
    : myXYZ(theX, theY, theZ) {}

Pnt3d::Pnt3d(const Naive_XYZ &theXYZ) : myXYZ(theXYZ) {}

Pnt3d::Pnt3d(const Naive_Point3d_t &thePnt)
    : myXYZ(thePnt.x, thePnt.y, thePnt.z) {}

const Pnt3d &Pnt3d::Origin() {
  static Pnt3d aPoint{0., 0., 0.};
  return aPoint;
}

const Pnt3d &Pnt3d::Unset() {
  static Pnt3d aPoint{};
  return aPoint;
}

void Pnt3d::SetXYZ(const Naive_Real theX, const Naive_Real theY,
                   const Naive_Real theZ) {
  SetX(theX);
  SetY(theY);
  SetZ(theZ);
}

Naive_Bool Pnt3d::IsValid() const {
  return Util::IsValidReal(myXYZ.x()) && Util::IsValidReal(myXYZ.y()) &&
         Util::IsValidReal(myXYZ.z());
}

Naive_Real Pnt3d::DistanceTo(const Pnt3d &thePoint) const {
  if (!IsValid() || !thePoint.IsValid())
    return math::Constant::UnsetReal();
  return (myXYZ - thePoint.myXYZ).norm();
}

Naive_Real Pnt3d::DistanceToSquared(const Pnt3d &thePoint) const {
  if (!IsValid() || !thePoint.IsValid())
    return math::Constant::UnsetReal();
  return (myXYZ - thePoint.myXYZ).squaredNorm();
}

Naive_Bool Pnt3d::Add(const Pnt3d &thePoint) {
  if (IsValid() && thePoint.IsValid()) {
    myXYZ += thePoint.XYZ();
    return Naive_True;
  }
  return Naive_False;
}

Pnt3d Pnt3d::Added(const Pnt3d &thePoint) const {
  Pnt3d aPnt(*this);
  return aPnt.Add(thePoint) ? aPnt : Unset();
}

Naive_Bool Pnt3d::Add(const Vec3d &theVector) {
  if (IsValid() && theVector.IsValid()) {
    myXYZ += theVector.XYZ();
    return Naive_True;
  }
  return Naive_False;
}

Pnt3d Pnt3d::Added(const Vec3d &theVector) const {
  Pnt3d aPnt(*this);
  return aPnt.Add(theVector) ? aPnt : Unset();
}

Vec3d Pnt3d::Subtracted(const Pnt3d &thePoint) const {
  if (IsValid() && thePoint.IsValid())
    return {myXYZ - thePoint.XYZ()};
  return Vec3d::Unset();
}

Naive_Bool Pnt3d::Multiply(const Naive_Real &theT) {
  if (IsValid() && Util::IsValidReal(theT)) {
    myXYZ *= theT;
    return Naive_True;
  }
  return Naive_False;
}

Pnt3d Pnt3d::Multiplied(const Naive_Real &theT) const {
  Pnt3d aPnt(*this);
  return aPnt.Multiply(theT) ? aPnt : Unset();
}

Naive_Bool Pnt3d::Divide(const Naive_Real &theT) {
  if (IsValid() && !Util::EpsilonEquals(theT, 0.0)) {
    myXYZ *= theT;
    return Naive_True;
  }
  return Naive_False;
}

Pnt3d Pnt3d::Divided(const Naive_Real &theT) const {
  Pnt3d aPnt(*this);
  return aPnt.Divide(theT) ? aPnt : Unset();
}

void Pnt3d::Negate() { myXYZ = -myXYZ; }

Pnt3d Pnt3d::Negated() const { return {-myXYZ}; }

Naive_Bool Pnt3d::Transform(const Trsf3d &theTrsf) {
  if (!IsValid() || !theTrsf.IsValid())
    return Naive_False;
  if (theTrsf.IsIdentity())
    return Naive_True;
  myXYZ = theTrsf.Affine() * myXYZ;
  return Naive_True;
}

Pnt3d Pnt3d::Transformed(const Trsf3d &theTrsf) const {
  Pnt3d aPnt(*this);
  return aPnt.Transform(theTrsf) ? aPnt : Unset();
}

Naive_Integer Pnt3d::CompareTo(const Pnt3d &thePoint) const {
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

Naive_Bool Pnt3d::Dump(Naive_Point3d_t &theP) const {
  if (!IsValid())
    return Naive_False;
  theP.x = X();
  theP.y = Y();
  theP.z = Z();
  return Naive_True;
}

const Pnt3d operator+(const Pnt3d &thePnt1, const Pnt3d &thePnt2) {
  return thePnt1.Added(thePnt2);
}

const Pnt3d operator+(const Pnt3d &thePnt, const Vec3d &theVec) {
  return thePnt.Added(theVec);
}

const Vec3d operator-(const Pnt3d &thePnt1, const Pnt3d &thePnt2) {
  return thePnt1.Subtracted(thePnt2);
}

const Pnt3d operator-(const Pnt3d &thePnt) { return thePnt.Negated(); }

const Pnt3d operator*(const Pnt3d &thePnt, const Naive_Real theT) {
  return thePnt.Multiplied(theT);
}

const Pnt3d operator*(const Naive_Real theT, const Pnt3d &thePnt) {
  return thePnt.Multiplied(theT);
}

const Pnt3d operator/(const Pnt3d &thePnt, const Naive_Real theT) {
  return thePnt.Divided(theT);
}

Naive_NAMESPACE_END(math);
