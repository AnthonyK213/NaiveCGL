#ifndef _NaiveCGL_BndShape_OrientedBoundingBox_HeaderFile
#define _NaiveCGL_BndShape_OrientedBoundingBox_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

class OrientedBoundingBox final {
public:

private:
  Naive_Plane m_plane;
  Naive_Interval m_x;
  Naive_Interval m_y;
  Naive_Interval m_z;
};

Naive_Namespace_End(bndshape);

#endif
