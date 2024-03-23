#ifndef _NaiveCGL_Geometry_NurbsCurve_HeaderFile
#define _NaiveCGL_Geometry_NurbsCurve_HeaderFile

#include "Point3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve final : std::enable_shared_from_this<NurbsCurve> {
public:
  Naive_EXPORT NurbsCurve();

private:
  Naive_Point3dList myPoles;
  Naive_RealList myKnots;
  Naive_RealList myWeigths;
  Naive_Integer myDegree;
};

Naive_NAMESPACE_END(geometry);

using Naive_NurbsCurve = naivecgl::geometry::NurbsCurve;

#endif
