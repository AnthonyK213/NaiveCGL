#ifndef _NaiveCGL_Geometry_Line_HeaderFile
#define _NaiveCGL_Geometry_Line_HeaderFile

#include "Vector3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Line final {
public:
  Naive_EXPORT Line() {}

  Naive_EXPORT Line(const Naive_Point3d &theFrom, const Naive_Point3d &theTo);

  Naive_EXPORT Line(const Naive_Point3d &theStart,
                    const Naive_Vector3d &theDirection,
                    const Naive_Real theLength);

  Naive_EXPORT Line(const Naive_Point3d &theStart,
                    const Naive_Vector3d &theSpan);

  Naive_EXPORT Line(const Naive_Line_T &theL);

  Naive_EXPORT Naive_Vector3d Direction() const { return myTo - myFrom; }

  Naive_EXPORT Naive_Vector3d UnitTangent() const;

  Naive_EXPORT const Naive_Point3d &From() const { return myFrom; }

  Naive_EXPORT const Naive_Point3d &To() const { return myTo; }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Real Length() const { return myFrom.DistanceTo(myTo); }

  Naive_EXPORT Naive_Real DistanceTo(const Naive_Point3d &thePnt,
                                     const Naive_Bool theFinite = true) const;

  Naive_EXPORT Naive_Point3d PointAt(const Naive_Real theT) const;

  Naive_EXPORT Naive_Point3d PointAtLength(const Naive_Real theLength) const;

  Naive_EXPORT void Dump(Naive_Line_T &theL) const;

private:
  Naive_Point3d myFrom;
  Naive_Point3d myTo;
};

Naive_NAMESPACE_END(geometry);

using Naive_Line = naivecgl::geometry::Line;

#endif
