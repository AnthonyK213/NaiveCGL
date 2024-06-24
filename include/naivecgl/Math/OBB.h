#ifndef _NaiveCGL_Math_OBB_HeaderFile
#define _NaiveCGL_Math_OBB_HeaderFile

#include "Pnt3d.h"
#include "Vec3d.h"

Naive_NAMESPACE_BEGIN(math);

class OBB final {
public:
private:
  Naive_Pnt3d myCenter;
  Naive_Vec3d myAxes[3];
  Naive_Real myHDims[3];
};

Naive_NAMESPACE_END(math);

using Naive_OBB = ::naivecgl::math::OBB;

#endif
