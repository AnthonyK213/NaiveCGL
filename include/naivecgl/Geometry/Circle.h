#ifndef _NaiveCGL_Geometry_Circle_Header
#define _NaiveCGL_Geometry_Circle_Header

#include "Plane.h"

Naive_Namespace_Begin(geometry);

class Naive_Export Circle final {
public:
private:
  Plane m_plane;
  Naive_Real m_radius;
};

Naive_Namespace_End(geometry);

#endif
