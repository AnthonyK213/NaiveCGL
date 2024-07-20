#ifndef _NaiveCGL_Geometry_Ellipse_HeaderFile
#define _NaiveCGL_Geometry_Ellipse_HeaderFile

#include "Conic.h"

Naive_NAMESPACE_BEGIN(geometry);

class Ellipse : public Naive_Conic {
public:
  Naive_DEFINE_RTTI(Ellipse, Naive_Conic);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_Ellipse = ::naivecgl::geometry::Ellipse;
Naive_DEFINE_HANDLE(Naive_Ellipse);

#endif
