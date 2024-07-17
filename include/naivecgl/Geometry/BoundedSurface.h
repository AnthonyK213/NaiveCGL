#ifndef _NaiveCGL_Geometry_BoundedSurface_HeaderFile
#define _NaiveCGL_Geometry_BoundedSurface_HeaderFile

#include "Surface.h"

Naive_NAMESPACE_BEGIN(geometry);

class BoundedSurface : public Naive_Surface {
public:
  Naive_DEFINE_RTTI(BoundedSurface, Naive_Surface);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_BoundedSurface = ::naivecgl::geometry::BoundedSurface;
Naive_DEFINE_HANDLE(Naive_BoundedSurface);

#endif
