﻿#ifndef _NaiveCGL_BndShape_OBB_HeaderFile
#define _NaiveCGL_BndShape_OBB_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_NAMESPACE_BEGIN(bndshape);

class OBB final {
public:
private:
  Naive_Point3d myCenter;
  Naive_Vector3d myAxes[3];
  Naive_Real myHDims[3];
};

Naive_NAMESPACE_END(bndshape);

#endif