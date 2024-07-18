#ifndef _NaiveCGL_Geometry_Conic_HeaderFile
#define _NaiveCGL_Geometry_Conic_HeaderFile

#include "../Math/Ax2.h"
#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry);

class Conic : public Naive_Curve {
public:
  Naive_DEFINE_RTTI(Conic, Naive_Curve);

protected:
  Naive_Ax2 myPos;
};

Naive_NAMESPACE_END(geometry);

using Naive_Conic = ::naivecgl::geometry::Conic;
Naive_DEFINE_HANDLE(Naive_Conic);

#endif
