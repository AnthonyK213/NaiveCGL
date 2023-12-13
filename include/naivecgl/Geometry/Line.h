#ifndef _NaiveCGL_Geometry_Line_Header
#define _NaiveCGL_Geometry_Line_Header

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export Line final {
public:

private:
  Naive_Point3d m_from;
  Naive_Point3d m_to;
};

Naive_Namespace_End(geometry);

#endif
