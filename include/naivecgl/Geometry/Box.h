#ifndef _NaiveCGL_Geometry_Box_HeaderFile
#define _NaiveCGL_Geometry_Box_HeaderFile

#include "Point3d.h"
#include "Vector3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Box final {
public:
  Naive_EXPORT Box();

  Naive_EXPORT Box(const Naive_Point3d &theA, const Naive_Point3d &theB);

  Naive_EXPORT static const Box &Unset();

  Naive_EXPORT static const Box &Void();

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool IsVoid() const;

  Naive_EXPORT Naive_Bool IsPoint() const;

  Naive_EXPORT const Naive_Point3d &Min() const { return myMin; }

  Naive_EXPORT const Naive_Point3d &Max() const { return myMax; }

  Naive_EXPORT Naive_Vector3d Diagonal() const { return myMax - myMin; }

  Naive_EXPORT Naive_Point3d Center() const { return 0.5 * (myMax + myMin); }

  Naive_EXPORT void Update(const Naive_Real theXMin, const Naive_Real theYMin,
                           const Naive_Real theZMin, const Naive_Real theXMax,
                           const Naive_Real theYMax, const Naive_Real theZMax);

  Naive_EXPORT void Update(const Naive_Real theX, const Naive_Real theY,
                           const Naive_Real theZ);

  Naive_EXPORT void Add(const Box &theOther);

  Naive_EXPORT void Add(const Naive_Point3d &thePoint);

private:
  Naive_Bool isSet() const;

  Naive_Bool isValid() const;

  Naive_Bool isVoid() const;

  Naive_Bool isPoint() const;

private:
  Naive_Point3d myMin;
  Naive_Point3d myMax;
};

Naive_NAMESPACE_END(geometry);

using Naive_Box = ::naivecgl::geometry::Box;

#endif
