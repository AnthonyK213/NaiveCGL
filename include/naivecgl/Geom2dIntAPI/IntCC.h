#ifndef _NaiveCGL_Geom2dIntAPI_IntCC_HeaderFile
#define _NaiveCGL_Geom2dIntAPI_IntCC_HeaderFile

#include "../Common/Handle.h"
#include "../Math/Precision.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class NurbsCurve;

Naive_NAMESPACE_END(geometry2d);

Naive_NAMESPACE_BEGIN(geom2dintapi);

class IntCC final {
public:
  Naive_EXPORT IntCC(const Naive_Handle<geometry2d::NurbsCurve> &theC1,
                     const Naive_Handle<geometry2d::NurbsCurve> &theC2,
                     const Naive_Real theTol);

private:
};

Naive_NAMESPACE_END(geom2dintapi);

#endif
