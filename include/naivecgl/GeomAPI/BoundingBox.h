#ifndef _NaiveCGL_GeomAPI_BoundingBox_HeaderFile
#define _NaiveCGL_GeomAPI_BoundingBox_HeaderFile

#include "../Math/Box.h"
#include "../Math/OBB.h"

Naive_NAMESPACE_BEGIN(geom_api);

class BoundingBox final {
public:
  Naive_EXPORT static Naive_Code
  BoxFromPoints(const Naive_Pnt3dList1 &thePoints, Naive_Box &theBox);

  Naive_EXPORT static Naive_Code
  OBBFromPoints(const Naive_Pnt3dList1 &thePoints, Naive_OBB &theOBB);
};

Naive_NAMESPACE_END(geom_api);

#endif
