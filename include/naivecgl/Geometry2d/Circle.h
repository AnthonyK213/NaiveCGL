#ifndef _NaiveCGL_Geometry2d_Circle_HeaderFile
#define _NaiveCGL_Geometry2d_Circle_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Circle : public Naive_Conic2d {
public:
  Naive_DEFINE_RTTI(Circle, Naive_Conic2d);

protected:
private:
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Circle2d = ::naivecgl::geometry2d::Circle;
Naive_DEFINE_HANDLE(Naive_Circle2d);

#endif
