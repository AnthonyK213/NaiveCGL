#ifndef _NaiveCGL_Geometry_RectangularTrimmedSurface_HeaderFile
#define _NaiveCGL_Geometry_RectangularTrimmedSurface_HeaderFile

#include "BoundedSurface.h"

Naive_NAMESPACE_BEGIN(geometry);

class RectangularTrimmedSurface : public Naive_BoundedSurface {
public:
  Naive_DEFINE_RTTI(RectangularTrimmedSurface, Naive_BoundedSurface);

private:
};

Naive_NAMESPACE_END(geometry);

using Naive_RectangularTrimmedSurface =
    ::naivecgl::geometry::RectangularTrimmedSurface;
Naive_DEFINE_HANDLE(Naive_RectangularTrimmedSurface);

#endif
