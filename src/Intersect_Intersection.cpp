#include <naivecgl/Intersect/Intersection.h>

Naive_NAMESPACE_BEGIN(intersect);

Naive_Bool Intersection::LinePlane(const Naive_Line &theLine,
                                   const Naive_Plane &thePlane,
                                   Naive_Real &theT) {
  if (!theLine.IsValid() || !thePlane.IsValid())
    return false;

  Naive_XYZ PL = theLine.From().XYZ() - thePlane.Location().XYZ();
  const Naive_XYZ &l = theLine.Direction().XYZ();
  const Naive_XYZ &n = thePlane.Axis().XYZ();
  Naive_Real d = l.dot(n);

  if (std::abs(d) <= math::ZeroTolerance)
    return false;

  theT = PL.dot(n) / d;

  return true;
}

Naive_NAMESPACE_END(intersect);
