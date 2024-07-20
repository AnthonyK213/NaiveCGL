#ifndef _NaiveCGL_Geometry_SphericalSurface_HeaderFile
#define _NaiveCGL_Geometry_SphericalSurface_HeaderFile

#include "ElementarySurface.h"

Naive_NAMESPACE_BEGIN(geometry);

class SphericalSurface : public Naive_ElementarySurface {
public:
  Naive_DEFINE_RTTI(SphericalSurface, Naive_ElementarySurface);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_SphericalSurface = ::naivecgl::geometry::SphericalSurface;
Naive_DEFINE_HANDLE(Naive_SphericalSurface);

#endif
