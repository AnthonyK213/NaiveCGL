#ifndef _NaiveCGL_Geometry_Line_HeaderFile
#define _NaiveCGL_Geometry_Line_HeaderFile

#include "def.h"

Naive_Namespace_Begin(geometry);

class Naive_Export Line final {
public:
private:
  Naive_Point3d myFrom;
  Naive_Point3d myTo;
};

Naive_Namespace_End(geometry);

#endif
