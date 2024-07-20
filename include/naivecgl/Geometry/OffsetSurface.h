#ifndef _NaiveCGL_Geometry_OffsetSurface_HeaderFile
#define _NaiveCGL_Geometry_OffsetSurface_HeaderFile

#include "Surface.h"

Naive_NAMESPACE_BEGIN(geometry);

class OffsetSurface : public Naive_Surface {
public:
  Naive_DEFINE_RTTI(OffsetSurface, Naive_Surface);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_OffsetSurface = ::naivecgl::geometry::OffsetSurface;
Naive_DEFINE_HANDLE(Naive_OffsetSurface);

#endif
