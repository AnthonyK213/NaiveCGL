#include <naivecgl/Intersect/Intersection.h>

Naive_NAMESPACE_BEGIN(intersect);

Naive_Code Intersection::LinePlane(const Naive_Line &theLine,
                                   const Naive_Plane &thePlane,
                                   Naive_Real &theT) {
  if (!theLine.IsValid() || !thePlane.IsValid())
    return Naive_Code_invalid_value;

  Naive_XYZ LP = thePlane.Location().XYZ() - theLine.Location().XYZ();
  const Naive_XYZ &l = theLine.Direction().XYZ();
  const Naive_XYZ &n = thePlane.Axis().XYZ();
  Naive_Real d = l.dot(n);

  if (::std::abs(d) <= math::Constant::ZeroTolerance())
    return Naive_Code_no_intersection;

  theT = LP.dot(n) / d;

  return Naive_Code_ok;
}

Naive_NAMESPACE_END(intersect);
