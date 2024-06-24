#include <naivecgl/Intersect/Intersection.h>

Naive_NAMESPACE_BEGIN(intersect);

Naive_Code Intersection::LinePlane(const Handle_Naive_Line &theLine,
                                   const Handle_Naive_Plane &thePlane,
                                   Naive_Real &theT) {
  if (theLine.IsNull() || thePlane.IsNull())
    return Naive_Code_null_arg_address;

  if (!theLine->IsValid() || !thePlane->IsValid())
    return Naive_Code_invalid_handle;

  const Naive_Pln aPln = thePlane->Pln();
  Naive_XYZ LP = aPln.Location().XYZ() - theLine->Location().XYZ();
  const Naive_XYZ &l = theLine->Direction().XYZ();
  const Naive_XYZ &n = aPln.Axis().XYZ();
  Naive_Real d = l.dot(n);

  if (::std::abs(d) <= math::Constant::ZeroTolerance())
    return Naive_Code_no_intersection;

  theT = LP.dot(n) / d;

  return Naive_Code_ok;
}

Naive_NAMESPACE_END(intersect);
