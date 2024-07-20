#ifndef _NaiveCGL_Geometry_ConicalSurface_HeaderFile
#define _NaiveCGL_Geometry_ConicalSurface_HeaderFile

#include "ElementarySurface.h"

Naive_NAMESPACE_BEGIN(geometry);

class ConicalSurface : public Naive_ElementarySurface {
public:
  Naive_DEFINE_RTTI(ConicalSurface, Naive_ElementarySurface);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_ConicalSurface = ::naivecgl::geometry::ConicalSurface;
Naive_DEFINE_HANDLE(Naive_ConicalSurface);

#endif
