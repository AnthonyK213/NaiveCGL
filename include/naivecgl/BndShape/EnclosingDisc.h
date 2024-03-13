#ifndef _NaiveCGL_BndShape_EnclosingDisc_HeaderFile
#define _NaiveCGL_BndShape_EnclosingDisc_HeaderFile

#include <naivecgl/Geometry/Point2d.h>
#include <naivecgl/Geometry/Vector3d.h>

Naive_NAMESPACE_BEGIN(bndshape);

Naive_EXPORT Naive_Bool
EnclosingDisc(const Naive_List<Naive_Point2d> &thePoints,
              Naive_Point2d &theOrigin, Naive_Real &theRadius);

Naive_NAMESPACE_END(bndshape);

#endif
