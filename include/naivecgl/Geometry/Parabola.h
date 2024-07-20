#ifndef _NaiveCGL_Geometry_Parabola_HeaderFile
#define _NaiveCGL_Geometry_Parabola_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry);

class Parabola : public Naive_Conic {
public:
  Naive_DEFINE_RTTI(Parabola, Naive_Conic);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_Parabola = ::naivecgl::geometry::Parabola;
Naive_DEFINE_HANDLE(Naive_Parabola);

#endif
