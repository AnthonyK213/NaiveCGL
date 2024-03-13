#include <naivecgl/Geometry/Line.h>

Naive_NAMESPACE_BEGIN(geometry);

Line::Line(const Naive_Point3d &theFrom, const Naive_Point3d &theTo)
    : myFrom(theFrom), myTo(theTo) {}

Line::Line(const Naive_Point3d &theStart, const Naive_Vector3d &theDirection,
           const Naive_Real theLength) {}

Line::Line(const Naive_Point3d &theStart, const Naive_Vector3d &theSpan) {}

Line::Line(const Naive_Line_T &theL) : myFrom(theL.from), myTo(theL.to) {}

Naive_Real Line::DistanceTo(const Naive_Point3d &thePnt,
                            const Naive_Bool theFinite) const {
  return 0;
}

Naive_Point3d Line::PointAt(const Naive_Real theT) const { return {}; }

Naive_Point3d Line::PointAtLength(const Naive_Real theLength) const {
  return {};
}

void Line::Dump(Naive_Line_T &theL) const {
  myFrom.Dump(theL.from);
  myTo.Dump(theL.to);
}

Naive_NAMESPACE_END(geometry);
