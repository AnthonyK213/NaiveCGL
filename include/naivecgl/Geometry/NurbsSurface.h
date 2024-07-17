#ifndef _NaiveCGL_Geometry_NurbsSurface_HeaderFile
#define _NaiveCGL_Geometry_NurbsSurface_HeaderFile

#include "../Math/Nurbs.h"
#include "../Math/Util.h"
#include "BoundedSurface.h"

Naive_NAMESPACE_BEGIN(geometry);

class NurbsCurve;

class NurbsSurface final : public Naive_BoundedSurface {
public:
  Naive_EXPORT NurbsSurface() noexcept;

  Naive_EXPORT NurbsSurface(
      const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
      const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
      const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
      const Naive_Integer theUDegree, const Naive_Integer theVDegree) noexcept;

  Naive_EXPORT Naive_Code
  Init(const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
       const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
       const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
       const Naive_Integer theUDegree, const Naive_Integer theVDegree) noexcept;

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Integer UDegree() const { return myUDegree; }

  Naive_EXPORT Naive_Integer VDegree() const { return myVDegree; }

  Naive_EXPORT Naive_Bool Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                 Naive_Real &theV0, Naive_Real &theV1) const;

  Naive_EXPORT Naive_Bool IsURational() const { return myURational; }

  Naive_EXPORT Naive_Bool IsVRational() const { return myVRational; }

  Naive_EXPORT Naive_Bool IsUPeriodic() const { return myUPeriodic; }

  Naive_EXPORT Naive_Bool IsVPeriodic() const { return myVPeriodic; }

  Naive_EXPORT virtual Naive_Pnt3d
  PointAt(const Naive_Real theU, const Naive_Real theV) const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theU, const Naive_Real theV,
           const Naive_Integer theN,
           Naive_Vec3dList1 &theD) const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(NurbsSurface, Naive_BoundedSurface);

private:
  template <typename P2, typename R2, typename R, typename I>
  Naive_Code update(P2 &&thePoles, R2 &&theWeights, R &&theUKnots,
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
  Naive_Pnt3dList2 myPoles;
  Naive_RealList2 myWeights;
  Naive_RealList1 myUFlatKnots;
  Naive_RealList1 myVFlatKnots;
  Naive_RealList1 myUKnots;
  Naive_RealList1 myVKnots;
  Naive_IntegerList1 myUMults;
  Naive_IntegerList1 myVMults;
  Naive_IntegerList1 myUSpanIdx;
  Naive_IntegerList1 myVSpanIdx;
};

Naive_NAMESPACE_END(geometry);

#include "detail/NurbsSurface.inl"

using Naive_NurbsSurface = ::naivecgl::geometry::NurbsSurface;
Naive_DEFINE_HANDLE(Naive_NurbsSurface);

#endif
