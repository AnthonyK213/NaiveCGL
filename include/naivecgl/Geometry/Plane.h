#ifndef _NaiveCGL_Geometry_Plane_HeaderFile
#define _NaiveCGL_Geometry_Plane_HeaderFile

#include "def.h"

Naive_Namespace_Begin(geometry);

class Plane final {
public:
private:
  Naive_Point3d myOrigin;
  Naive_Vector3d myXAxis;
  Naive_Vector3d myYAxis;
  Naive_Vector3d myZAxis;
};

Naive_Namespace_End(geometry);

#endif
