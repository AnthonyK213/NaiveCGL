#ifndef _NaiveCGL_Geometry_Hyperbola_HeaderFile
#define _NaiveCGL_Geometry_Hyperbola_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry);

class Hyperbola : public Naive_Conic {
public:
  Naive_DEFINE_RTTI(Hyperbola, Naive_Conic);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_Hyperbola = ::naivecgl::geometry::Hyperbola;
Naive_DEFINE_HANDLE(Naive_Hyperbola);

#endif
