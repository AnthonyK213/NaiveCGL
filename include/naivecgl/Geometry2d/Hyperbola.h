#ifndef _NaiveCGL_Geometry2d_Hyperbola_HeaderFile
#define _NaiveCGL_Geometry2d_Hyperbola_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Hyperbola : public Naive_Conic2d {
public:
  Naive_DEFINE_RTTI(Hyperbola, Naive_Conic2d);

protected:
private:
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Hyperbola2d = ::naivecgl::geometry2d::Hyperbola;
Naive_DEFINE_HANDLE(Naive_Hyperbola2d);

#endif
