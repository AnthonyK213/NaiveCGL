#ifndef _NaiveCGL_Math_Ax1_HeaderFile
#define _NaiveCGL_Math_Ax1_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"
#include "Pnt3d.h"
#include "Vec3d.h"

Naive_NAMESPACE_BEGIN(math);

class Trsf3d;

class Ax1 {
public:
  Naive_EXPORT Ax1() noexcept;

  Naive_EXPORT Ax1(const Naive_Pnt3d &theP, const Naive_Vec3d &theV) noexcept;

  Naive_EXPORT Ax1(const Naive_Axis1_sf_t &theAx1) noexcept;

  Naive_EXPORT static const Ax1 &Unset();

  Naive_EXPORT Naive_Bool IsValid() const;

  const Naive_Pnt3d &Location() const { return myLoc; }

  const Naive_Vec3d &Direction() const { return myDir; }

  void SetLocation(const Naive_Pnt3d &theP) { myLoc = theP; }

  void SetDirection(const Naive_Vec3d &theV) { myDir = theV.Normalized(); }

  Naive_EXPORT Naive_Bool Transform(const Trsf3d &theTrsf);

  Naive_EXPORT Ax1 Transformed(const Trsf3d &theTrsf) const;

  Naive_EXPORT Naive_Bool Dump(Naive_Axis1_sf_t &theAx1) const;

private:
  Naive_Pnt3d myLoc;
  Naive_Vec3d myDir;
};

Naive_NAMESPACE_END(math);

using Naive_Ax1 = ::naivecgl::math::Ax1;

#endif
