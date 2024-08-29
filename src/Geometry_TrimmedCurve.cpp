#include <naivecgl/Geometry/TrimmedCurve.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(TrimmedCurve);

TrimmedCurve::TrimmedCurve(const Handle_Naive_Curve &theCurve,
                           const Naive_Real theT1, const Naive_Real theT2)
    : myBasisCurve(theCurve->Clone()), myT1(theT1), myT2(theT2) {}

Naive_Bool TrimmedCurve::IsValid() const {
  return myBasisCurve && myBasisCurve->IsValid();
}

Handle_Naive_Geometry TrimmedCurve::Clone() const {
  return myBasisCurve ? new TrimmedCurve(myBasisCurve->Clone(), myT1, myT1)
                      : nullptr;
}

Naive_Real TrimmedCurve::FirstParameter() const { return myT1; }

Naive_Real TrimmedCurve::LastParameter() const { return myT2; }

Naive_Pnt3d TrimmedCurve::PointAt(const Naive_Real theT) const {
  return myBasisCurve ? myBasisCurve->PointAt(theT) : Naive_Pnt3d::Unset();
}

Naive_Vec3d TrimmedCurve::TangentAt(const Naive_Real theT) const {
  return myBasisCurve ? myBasisCurve->TangentAt(theT) : Naive_Vec3d::Unset();
}

Naive_Code TrimmedCurve::Evaluate(const Naive_Real theT,
                                  const Naive_Integer theN,
                                  Naive_Vec3dList1 &theD) const {
  return myBasisCurve ? myBasisCurve->Evaluate(theT, theN, theD)
                      : Naive_Code_invalid_object;
}

Naive_Code TrimmedCurve::CurvatureAt(const Naive_Real theT,
                                     Naive_Vec3d &theV) const {
  return myBasisCurve ? myBasisCurve->CurvatureAt(theT, theV)
                      : Naive_Code_invalid_object;
}

Naive_Pnt3d TrimmedCurve::EndPoint() const {
  return myBasisCurve ? myBasisCurve->PointAt(myT2) : Naive_Pnt3d::Unset();
}

Naive_Pnt3d TrimmedCurve::StartPoint() const {
  return myBasisCurve ? myBasisCurve->PointAt(myT1) : Naive_Pnt3d::Unset();
}

Naive_Code TrimmedCurve::transform(const Naive_Trsf3d &theTrsf) {
  return myBasisCurve->Transform(theTrsf);
}

Naive_NAMESPACE_END(geometry);
