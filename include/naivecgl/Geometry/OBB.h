#ifndef _NaiveCGL_Geometry_OBB_HeaderFile
#define _NaiveCGL_Geometry_OBB_HeaderFile

#include "Point3d.h"
#include "Vector3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class OBB final {
public:
private:
  Naive_Point3d myCenter;
  Naive_Vector3d myAxes[3];
  Naive_Real myHDims[3];
};

Naive_NAMESPACE_END(geometry);

using Naive_OBB = ::naivecgl::geometry::OBB;

#endif
