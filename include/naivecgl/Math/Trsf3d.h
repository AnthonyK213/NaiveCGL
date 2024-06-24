#ifndef _NaiveCGL_Math_Trsf3d_HeaderFile
#define _NaiveCGL_Math_Trsf3d_HeaderFile

#include "Constant.h"

Naive_NAMESPACE_BEGIN(math);

class Vec3d;

class Trsf3d final {
public:
  Naive_EXPORT Trsf3d();

  Naive_EXPORT Trsf3d(const Naive_Affine3d &theTrsf);

  Naive_EXPORT Trsf3d(const Naive_Transform3d_sf_t &theTrsf);

  Naive_EXPORT const Naive_Affine3d &Affine() const { return myAffine; }

  Naive_EXPORT Naive_Affine3d &ChangeTrsf() { return myAffine; }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool
  IsIdentity(const Naive_Real theTol = Constant::Epsilon()) const;

  Naive_EXPORT static const Trsf3d &Unset();

  Naive_EXPORT static const Trsf3d &Identity();

  Naive_EXPORT static Trsf3d Translation(const Vec3d &theVec);

private:
  Naive_Affine3d myAffine;
};

Naive_NAMESPACE_END(math);

using Naive_Trsf3d = ::naivecgl::math::Trsf3d;

#endif
