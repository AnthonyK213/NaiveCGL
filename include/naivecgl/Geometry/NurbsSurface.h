#ifndef _NaiveCGL_Geometry_NurbsSurface_HeaderFile
#define _NaiveCGL_Geometry_NurbsSurface_HeaderFile

#include "Point3d.h"
#include "Vector3d.h"

#include <naivecgl/Common/Handle.h>

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve;

class NurbsSurface final : public Naive_Transient {
public:
private:
};

Naive_NAMESPACE_END(geometry);

using Naive_NurbsSurface = ::naivecgl::geometry::NurbsSurface;
using Handle_Naive_NurbsSurface = Naive_Handle<Naive_NurbsSurface>;

#endif
