#ifndef _NaiveCGL_Geometry_Transform_HeaderFile
#define _NaiveCGL_Geometry_Transform_HeaderFile

#include "../Common/Handle.h"
#include "../Common/Macro.h"
#include "../Common/Type.h"
#include "../Math/Constant.h"

Naive_NAMESPACE_BEGIN(geometry);

class Vector3d;

class Transform3d final : public Naive_Transient {
public:
  Naive_EXPORT Transform3d();

  Naive_EXPORT Transform3d(const Naive_Trsf &theTrsf);

  Naive_EXPORT Transform3d(const Naive_Transform3d_sf_t &theTrsf);

  Naive_EXPORT const Naive_Trsf &Trsf() const { return myTrsf; }

  Naive_EXPORT Naive_Trsf &ChangeTrsf() { return myTrsf; }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool
  IsIdentity(const Naive_Real theTol = math::Constant::Epsilon()) const;

  Naive_EXPORT static const Transform3d &Unset();

  Naive_EXPORT static const Transform3d &Identity();

  Naive_EXPORT static Transform3d Translation(const Vector3d &theVec);

private:
  Naive_Trsf myTrsf;
};

Naive_NAMESPACE_END(geometry);

using Naive_Transform3d = ::naivecgl::geometry::Transform3d;
Naive_DEFINE_HANDLE(Naive_Transform3d);

#endif
