#ifndef _NaiveCGL_BndShape_EnclosingDisc_HeaderFile
#define _NaiveCGL_BndShape_EnclosingDisc_HeaderFile

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

Naive_Export Naive_Bool
EnclosingDisc(const Naive_List<Naive_Point2d> &thePoints,
              Naive_Point2d &theOrigin, Naive_Real &theRadius);

Naive_Namespace_End(bndshape);

#endif
