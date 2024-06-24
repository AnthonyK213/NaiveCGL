#ifndef _NaiveCGL_Math_Ax2_HeaderFile
#define _NaiveCGL_Math_Ax2_HeaderFile

#include "Ax1.h"

Naive_NAMESPACE_BEGIN(math);

class Trsf3d;

class Ax2 {
public:
  Naive_EXPORT Ax2() noexcept;

  Naive_EXPORT Ax2(const Naive_Pnt3d &theP, const Naive_Vec3d &theX,
                   const Naive_Vec3d &theY) noexcept;

  Naive_EXPORT Ax2(const Naive_Pnt3d &theP, const Naive_Vec3d &theV) noexcept;

  Naive_EXPORT Ax2(const Naive_Axis2_sf_t &theAx2) noexcept;

  const Naive_Ax1 &Axis() const { return myAxis; }

  const Naive_Pnt3d &Location() const { return myAxis.Location(); }

  const Naive_Vec3d &Direction() const { return myAxis.Direction(); }

  const Naive_Vec3d &XDirection() const { return myXDir; }

  const Naive_Vec3d &YDirection() const { return myYDir; }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool Dump(Naive_Axis2_sf_t &theAx2) const;

private:
  Naive_Ax1 myAxis;
  Naive_Vec3d myXDir;
  Naive_Vec3d myYDir;
};

Naive_NAMESPACE_END(math);

using Naive_Ax2 = ::naivecgl::math::Ax2;

#endif
