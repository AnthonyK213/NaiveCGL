#ifndef _NaiveCGL_Geometry2d_Line_HeaderFile
#define _NaiveCGL_Geometry2d_Line_HeaderFile

#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Line : public Naive_Curve2d {
public:
  Naive_DEFINE_RTTI(Lines, Naive_Curve2d);

private:
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Line2d = ::naivecgl::geometry2d::Line;
Naive_DEFINE_HANDLE(Naive_Line2d);

#endif
