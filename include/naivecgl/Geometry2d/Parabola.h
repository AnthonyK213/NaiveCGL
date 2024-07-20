#ifndef _NaiveCGL_Geometry2d_Parabola_HeaderFile
#define _NaiveCGL_Geometry2d_Parabola_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Parabola : public Naive_Conic2d {
public:
  Naive_DEFINE_RTTI(Parabola, Naive_Conic2d);

protected:
private:
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Parabola2d = ::naivecgl::geometry2d::Parabola;
Naive_DEFINE_HANDLE(Naive_Parabola2d);

#endif
