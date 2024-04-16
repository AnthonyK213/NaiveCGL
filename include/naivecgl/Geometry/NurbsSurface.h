#ifndef _NaiveCGL_Geometry_NurbsSurface_HeaderFile
#define _NaiveCGL_Geometry_NurbsSurface_HeaderFile

#include "Point3d.h"
#include "Vector3d.h"

#include <naivecgl/Common/Handle.h>

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve;

class NurbsSurface final : public Naive_Transient {
public:
  Naive_EXPORT NurbsSurface(
      const Naive_Point3dList2 &thePoles, const Naive_RealList2 &theWeights,
      const Naive_RealList &theUKnots, const Naive_RealList &theVKnots,
      const Naive_IntegerList &theUMults, const Naive_IntegerList &theVMults,
      const Naive_Integer theUDegree, const Naive_Integer theVDegree);

  Naive_EXPORT Naive_Integer UDegree() const { return myUDegree; }

  Naive_EXPORT Naive_Integer VDegree() const { return myVDegree; }

  Naive_EXPORT Naive_Bool Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                 Naive_Real &theV0, Naive_Real &theV1) const;

  Naive_EXPORT Naive_Bool IsURational() const { return myURational; }

  Naive_EXPORT Naive_Bool IsVRational() const { return myVRational; }

  Naive_EXPORT Naive_Bool IsUPeriodic() const { return myUPeriodic; }

  Naive_EXPORT Naive_Bool IsVPeriodic() const { return myVPeriodic; }

  Naive_EXPORT Naive_Point3d PointAt(const Naive_Real theU,
                                     const Naive_Real theV) const;

  Naive_EXPORT Naive_Bool Evaluate(const Naive_Real theU, const Naive_Real theV,
                                   const Naive_Integer theN,
                                   Naive_Vector3dList &theD) const;

private:
  Naive_Bool isValid() const;

private:
  Naive_Bool myURational;
  Naive_Bool myVRational;
  Naive_Bool myUPeriodic;
  Naive_Bool myVPeriodic;
  Naive_Integer myUDegree;
  Naive_Integer myVDegree;
  Naive_Point3dList2 myPoles;
  Naive_RealList2 myWeights;
  Naive_RealList myUFlatKnots;
  Naive_RealList myVFlatKnots;
  Naive_RealList myUKnots;
  Naive_RealList myVKnots;
  Naive_IntegerList myUMults;
  Naive_IntegerList myVMults;
  Naive_IntegerList myUSpanIdx;
  Naive_IntegerList myVSpanIdx;
};

Naive_NAMESPACE_END(geometry);

using Naive_NurbsSurface = ::naivecgl::geometry::NurbsSurface;
using Handle_Naive_NurbsSurface = Naive_Handle<Naive_NurbsSurface>;

#endif
