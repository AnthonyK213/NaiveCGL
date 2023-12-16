#ifndef _NaiveCGL_Geometry_Plane_Header
#define _NaiveCGL_Geometry_Plane_Header

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export Plane final {
public:

private:
  Naive_Point3d m_origin;
  Naive_Vector3d m_xAxis;
  Naive_Vector3d m_yAxis;
  Naive_Vector3d m_zAxis;
};

Naive_Namespace_End(geometry);

#endif
