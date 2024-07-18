#ifndef _NaiveCGL_Geometry2d_Conic_HeaderFile
#define _NaiveCGL_Geometry2d_Conic_HeaderFile

#include "Curve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Conic : public Naive_Curve2d {
public:
  Naive_DEFINE_RTTI(Conic, Naive_Curve2d);

protected:
private:
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Conic2d = ::naivecgl::geometry2d::Conic;
Naive_DEFINE_HANDLE(Naive_Conic2d);

#endif
