#ifndef _NaiveCGL_Geometry_NurbsSurface_HeaderFile
#define _NaiveCGL_Geometry_NurbsSurface_HeaderFile

#include "Surface.h"

#include <naivecgl/Common/Handle.h>
#include <naivecgl/Math/Nurbs.h>

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve;

class NurbsSurface final : public Surface {
public:
  Naive_EXPORT NurbsSurface(
      const Naive_Point3dList2 &thePoles, const Naive_RealList2 &theWeights,
      const Naive_RealList &theUKnots, const Naive_RealList &theVKnots,
      const Naive_IntegerList &theUMults, const Naive_IntegerList &theVMults,
      const Naive_Integer theUDegree, const Naive_Integer theVDegree);

  Naive_EXPORT virtual Naive_Bool IsValid() const override;

  Naive_EXPORT Naive_Integer UDegree() const { return myUDegree; }

  Naive_EXPORT Naive_Integer VDegree() const { return myVDegree; }

  Naive_EXPORT Naive_Bool Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                 Naive_Real &theV0, Naive_Real &theV1) const;

  Naive_EXPORT Naive_Bool IsURational() const { return myURational; }

  Naive_EXPORT Naive_Bool IsVRational() const { return myVRational; }

  Naive_EXPORT Naive_Bool IsUPeriodic() const { return myUPeriodic; }

  Naive_EXPORT Naive_Bool IsVPeriodic() const { return myVPeriodic; }

  Naive_EXPORT virtual Naive_Point3d
  PointAt(const Naive_Real theU, const Naive_Real theV) const override;

  Naive_EXPORT virtual Naive_Bool
  Evaluate(const Naive_Real theU, const Naive_Real theV,
           const Naive_Integer theN, Naive_Vector3dList &theD) const override;

private:
  template <typename P2, typename R2, typename R, typename I>
  Naive_Bool update(P2 &&thePoles, R2 &&theWeights, R &&theUKnots,
                    R &&theVKnots, I &&theUMults, I &&theVMults,
                    const Naive_Integer theUDegree,
                    const Naive_Integer theVDegree);

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

#include "detail/NurbsSurface.inl"

using Naive_NurbsSurface = ::naivecgl::geometry::NurbsSurface;
Naive_DEFINE_HANDLE(Naive_NurbsSurface);

#endif
