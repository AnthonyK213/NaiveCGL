#ifndef _NaiveCGL_Geometry2d_CartesianPoint2d_HeaderFile
#define _NaiveCGL_Geometry2d_CartesianPoint2d_HeaderFile

#include "Point2d.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class CartesianPoint2d final : public Naive_Point2d {
public:
  Naive_EXPORT CartesianPoint2d();

  Naive_EXPORT CartesianPoint2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT CartesianPoint2d(const Naive_Pnt2d &thePnt2d);

  Naive_EXPORT virtual Naive_Pnt2d Pnt2d() const Naive_OVERRIDE {
    return myPnt2d;
  }

  Naive_EXPORT virtual Naive_Real X() const Naive_OVERRIDE {
    return myPnt2d.X();
  }

  Naive_EXPORT virtual Naive_Real Y() const Naive_OVERRIDE {
    return myPnt2d.Y();
  }

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry2d Clone() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(CartesianPoint2d, Naive_Point2d);

private:
  Naive_Pnt2d myPnt2d;
};

Naive_NAMESPACE_END(geometry2d);

using Naive_CartesianPoint2d = ::naivecgl::geometry2d::CartesianPoint2d;
Naive_DEFINE_HANDLE(Naive_CartesianPoint2d);

#endif
