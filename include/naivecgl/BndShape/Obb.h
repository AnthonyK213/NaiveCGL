#ifndef _NaiveCGL_BndShape_Obb_HeaderFile
#define _NaiveCGL_BndShape_Obb_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_NAMESPACE_BEGIN(bndshape);

class Obb final {
public:
private:
  Naive_Point3d myCenter;
  Naive_Vector3d myAxes[3];
  Naive_Real myHDims[3];
};

Naive_NAMESPACE_END(bndshape);

#endif
