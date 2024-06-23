#ifndef _NaiveCGL_Geometry_OBB_HeaderFile
#define _NaiveCGL_Geometry_OBB_HeaderFile

#include "../Math/Pnt3d.h"
#include "../Math/Vec3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class OBB final {
public:
private:
  Naive_Pnt3d myCenter;
  Naive_Vec3d myAxes[3];
  Naive_Real myHDims[3];
};

Naive_NAMESPACE_END(geometry);

using Naive_OBB = ::naivecgl::geometry::OBB;

#endif
