#ifndef _NaiveCGL_Geometry_Point3d_HeaderFile
#define _NaiveCGL_Geometry_Point3d_HeaderFile

#include "../Math/Pnt3d.h"
#include "../Math/Trsf3d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry);

class Point3d final : public Naive_Geometry {
public:
  Naive_EXPORT Point3d();

  Naive_EXPORT Point3d(const Naive_Real theX, const Naive_Real theY,
                       const Naive_Real theZ);

  Naive_EXPORT Point3d(const Naive_Pnt3d &thePnt);

  Naive_EXPORT void SetPnt(const Naive_Pnt3d &thePnt) { myPnt = thePnt; }

  Naive_EXPORT void SetX(const Naive_Real &theX) { myPnt.SetX(theX); }

  Naive_EXPORT void SetY(const Naive_Real &theY) { myPnt.SetY(theY); }

  Naive_EXPORT void SetZ(const Naive_Real &theZ) { myPnt.SetZ(theZ); }

  Naive_EXPORT const Naive_Pnt3d &Pnt() const { return myPnt; }

  Naive_EXPORT Naive_Real X() const { return myPnt.X(); }

  Naive_EXPORT Naive_Real Y() const { return myPnt.Y(); }

  Naive_EXPORT Naive_Real Z() const { return myPnt.Z(); }

  Naive_EXPORT Naive_Real DistanceTo(const Naive_Handle<Point3d> &theP) const;

  Naive_EXPORT Naive_Real
  DistanceToSquared(const Naive_Handle<Point3d> &theP) const;

  Naive_EXPORT void Transform(const Naive_Trsf3d &theTrsf);

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Point3d, Naive_Geometry, Naive_Class_point3d);

private:
  Naive_Pnt3d myPnt;
};

Naive_NAMESPACE_END(geometry);

using Naive_Point3d = ::naivecgl::geometry::Point3d;
Naive_DEFINE_HANDLE(Naive_Point3d);
using Naive_Point3dList1 = Naive_List1<Handle_Naive_Point3d>;
using Naive_Point3dList2 = Naive_List2<Handle_Naive_Point3d>;

#endif
