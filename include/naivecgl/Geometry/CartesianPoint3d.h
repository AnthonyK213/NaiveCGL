#ifndef _NaiveCGL_Geometry_CartesianPoint3d_HeaderFile
#define _NaiveCGL_Geometry_CartesianPoint3d_HeaderFile

#include "Point3d.h"

Naive_NAMESPACE_BEGIN(geometry);

class CartesianPoint3d final : public Naive_Point3d {
public:
  Naive_EXPORT CartesianPoint3d();

  Naive_EXPORT CartesianPoint3d(const Naive_Real theX, const Naive_Real theY,
                                const Naive_Real theZ);

  Naive_EXPORT CartesianPoint3d(const Naive_Pnt3d &thePnt);

  Naive_EXPORT CartesianPoint3d(const Naive_Point_sf_t &theSF);

  Naive_EXPORT void SetPnt(const Naive_Pnt3d &thePnt) { myPnt = thePnt; }

  Naive_EXPORT void SetX(const Naive_Real &theX) { myPnt.SetX(theX); }

  Naive_EXPORT void SetY(const Naive_Real &theY) { myPnt.SetY(theY); }

  Naive_EXPORT void SetZ(const Naive_Real &theZ) { myPnt.SetZ(theZ); }

  Naive_EXPORT virtual Naive_Pnt3d Pnt() const Naive_OVERRIDE { return myPnt; }

  Naive_EXPORT virtual Naive_Real X() const Naive_OVERRIDE { return myPnt.X(); }

  Naive_EXPORT virtual Naive_Real Y() const Naive_OVERRIDE { return myPnt.Y(); }

  Naive_EXPORT virtual Naive_Real Z() const Naive_OVERRIDE { return myPnt.Z(); }

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry Clone() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(CartesianPoint3d, Naive_Point3d);

protected:
  Naive_EXPORT virtual Naive_Code
  transform(const math::Trsf3d &theTrsf) Naive_OVERRIDE;

private:
  Naive_Pnt3d myPnt;
};

Naive_NAMESPACE_END(geometry);

using Naive_CartesianPoint3d = ::naivecgl::geometry::CartesianPoint3d;
Naive_DEFINE_HANDLE(Naive_CartesianPoint3d);

#endif
