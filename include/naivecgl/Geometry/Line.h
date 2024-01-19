#ifndef _NaiveCGL_Geometry_Line_HeaderFile
#define _NaiveCGL_Geometry_Line_HeaderFile

#include "def.h"

Naive_NAMESPACE_BEGIN(geometry);

class Line final {
public:
private:
  Naive_Point3d myFrom;
  Naive_Point3d myTo;
};

Naive_NAMESPACE_END(geometry);

#endif
