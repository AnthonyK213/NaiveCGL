#ifndef _NaiveCGL_BndShape_EnclosingDisc_Header
#define _NaiveCGL_BndShape_EnclosingDisc_Header

#include <naivecgl/Common/geometry.h>

Naive_Namespace_Begin(bndshape);

Naive_Export Naive_Bool enclosingDisc(const Naive_List<Naive_Point2d> &points,
                                      Naive_Point2d &origin,
                                      Naive_Real &radius);

Naive_Namespace_End(bndshape);

#endif
