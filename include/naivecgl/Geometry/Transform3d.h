#ifndef _NaiveCGL_Geometry_Transform_HeaderFile
#define _NaiveCGL_Geometry_Transform_HeaderFile

#include "../Common/Handle.h"
#include "../Common/Macro.h"
#include "../Common/Type.h"
#include "../Math/Constant.h"
#include "../Math/Trsf3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class Transform3d final : public Naive_Transient {
public:
  Naive_EXPORT Transform3d();

  Naive_EXPORT Transform3d(const Naive_Trsf3d &theTrsf);

  Naive_EXPORT const Naive_Trsf3d &Trsf() const { return myTrsf; }

  Naive_EXPORT Naive_Bool IsValid() const;

private:
  Naive_Trsf3d myTrsf;
};

Naive_NAMESPACE_END(geometry);

using Naive_Transform3d = ::naivecgl::geometry::Transform3d;
Naive_DEFINE_HANDLE(Naive_Transform3d);

#endif
