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
      const Naive_Integer theUDegree, const Naive_Integer theVDegree,
      const Naive_Bool theUPeriodic = Naive_False,
      const Naive_Bool theVPeriodic = Naive_False) noexcept;

  Naive_EXPORT NurbsSurface(const Naive_NurbsSurface_sf_t &theSF) noexcept;

  Naive_EXPORT Naive_Code
  Init(const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
       const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
       const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
       const Naive_Integer theUDegree, const Naive_Integer theVDegree,
       const Naive_Bool theUPeriodic = Naive_False,
       const Naive_Bool theVPeriodic = Naive_False) noexcept;

  Naive_EXPORT Naive_Code Init(const Naive_NurbsSurface_sf_t &theSF) noexcept;

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Integer UDegree() const { return myUDegree; }

  Naive_EXPORT Naive_Integer VDegree() const { return myVDegree; }

  Naive_EXPORT virtual Naive_Bool
  Bounds(Naive_Real &theU0, Naive_Real &theU1, Naive_Real &theV0,
         Naive_Real &theV1) const Naive_OVERRIDE;

  Naive_EXPORT Naive_Bool IsURational() const { return myURational; }

  Naive_EXPORT Naive_Bool IsVRational() const { return myVRational; }

  Naive_EXPORT virtual Naive_Bool IsUClosed() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsVClosed() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsUPeriodic() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Bool IsVPeriodic() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real UPeriod() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Real VPeriod() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code
  Evaluate(const Naive_Real theU, const Naive_Real theV,
           const Naive_Integer theN,
           Naive_Vec3dList2 &theD) const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(NurbsSurface, Naive_BoundedSurface);

protected:
  Naive_EXPORT virtual Naive_Code
  transform(const math::Trsf3d &theTrsf) Naive_OVERRIDE;

private:
  template <typename CPs2_, typename Knots_, typename Mults_>
  Naive_Code
  update(CPs2_ &&theCPs, Knots_ &&theUKnots, Knots_ &&theVKnots,
         Mults_ &&theUMults, Mults_ &&theVMults, const Naive_Integer theUDegree,
         const Naive_Integer theVDegree, const Naive_Bool theUPeriodic,
         const Naive_Bool theVPeriodic);

private:
  Naive_XYZWList2 myCPs;
  Naive_RealList1 myUFlatKnots;
  Naive_RealList1 myVFlatKnots;
  Naive_RealList1 myUKnots;
  Naive_RealList1 myVKnots;
  Naive_IntegerList1 myUMults;
  Naive_IntegerList1 myVMults;
  Naive_Integer myUDegree;
  Naive_Integer myVDegree;
  Naive_Bool myURational;
  Naive_Bool myVRational;
  Naive_Bool myUPeriodic;
  Naive_Bool myVPeriodic;
};

Naive_NAMESPACE_END(geometry);

#include "detail/NurbsSurface.inl"

using Naive_NurbsSurface = ::naivecgl::geometry::NurbsSurface;
Naive_DEFINE_HANDLE(Naive_NurbsSurface);

#endif
