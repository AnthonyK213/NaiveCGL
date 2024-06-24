#ifndef _NaiveCGL_Geometry_ElementarySurface_HeaderFile
#define _NaiveCGL_Geometry_ElementarySurface_HeaderFile

#include "../Math/Ax2.h"
#include "Surface.h"

Naive_NAMESPACE_BEGIN(geometry);

class ElementarySurface : public Naive_Surface {
public:
protected:
  Naive_Ax2 myPos;
};

Naive_NAMESPACE_END(geometry);

using Naive_ElementarySurface = ::naivecgl::geometry::ElementarySurface;
Naive_DEFINE_HANDLE(Naive_ElementarySurface);

#endif
