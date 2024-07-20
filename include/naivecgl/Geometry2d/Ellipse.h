#ifndef _NaiveCGL_Geometry2d_Ellipse_HeaderFile
#define _NaiveCGL_Geometry2d_Ellipse_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Ellipse : public Naive_Conic2d {
public:
  Naive_DEFINE_RTTI(Ellipse, Naive_Conic2d);

protected:
private:
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Ellipse2d = ::naivecgl::geometry2d::Ellipse;
Naive_DEFINE_HANDLE(Naive_Ellipse2d);

#endif
