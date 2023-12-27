﻿#ifndef _NaiveCGL_Geometry_Rectangle_HeaderFile
#define _NaiveCGL_Geometry_Rectangle_HeaderFile

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export Rectangle final {
public:

private:
  Plane m_plane;
  Interval m_x;
  Interval m_y;
};

Naive_Namespace_End(geometry);

#endif
