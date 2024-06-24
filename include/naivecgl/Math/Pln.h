#ifndef _NaiveCGL_Math_Pln_HeaderFile
#define _NaiveCGL_Math_Pln_HeaderFile

#include "Ax2.h"

Naive_NAMESPACE_BEGIN(math);

class Trsf3d;

class Pln final {
public:
  Naive_EXPORT Pln();

  Naive_EXPORT Pln(const Naive_Ax2 &theAx2);

  Naive_EXPORT Pln(const Naive_Pnt3d &theP, const Naive_Vec3d &theXAxis,
                   const Naive_Vec3d &theYAxis);

  Naive_EXPORT Pln(const Naive_Pnt3d &theP, const Naive_Vec3d &theN);

  Naive_EXPORT Pln(const Naive_Plane_sf_t &thePln);

  Naive_EXPORT Naive_Bool IsValid() const;

  const Naive_Ax2 &Ax2() const { return myPos; }

  Naive_EXPORT const Naive_Pnt3d &Location() const { return myPos.Location(); }

  Naive_EXPORT const Naive_Vec3d &XAxis() const { return myPos.XDirection(); }

  Naive_EXPORT const Naive_Vec3d &YAxis() const { return myPos.YDirection(); }

  Naive_EXPORT const Naive_Vec3d &Axis() const { return myPos.Direction(); }

  Naive_EXPORT Naive_Real Distance(const Naive_Pnt3d &theP) const;

  Naive_EXPORT static const Pln &Unset();

  Naive_EXPORT static const Pln &WorldXY();

  Naive_EXPORT static const Pln &WorldYZ();

  Naive_EXPORT static const Pln &WorldZX();

  Naive_EXPORT Naive_Bool Transform(const Trsf3d &theTrsf);

  Naive_EXPORT Pln Transformed(const Trsf3d &theTrsf) const;

  Naive_EXPORT Naive_Bool Dump(Naive_Plane_sf_t &thePln) const;

  Naive_EXPORT static Naive_Bool Orient(const Pln &thePln1, const Pln &thePln2,
                                        Trsf3d &theTrsf);

private:
  void initInvalid();

  Naive_Bool initByXY();

  Naive_Bool initByZX();

private:
  Naive_Ax2 myPos;
};

Naive_NAMESPACE_END(math);

using Naive_Pln = ::naivecgl::math::Pln;

#endif
