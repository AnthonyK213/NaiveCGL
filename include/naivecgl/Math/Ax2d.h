#ifndef _NaiveCGL_Math_Ax2d_HeaderFile
#define _NaiveCGL_Math_Ax2d_HeaderFile

#include "Pnt2d.h"
#include "Vec2d.h"

Naive_NAMESPACE_BEGIN(math);

class Ax2d final {
public:
  Naive_EXPORT Ax2d();

  Naive_EXPORT Ax2d(const Naive_Pnt2d &theP, const Naive_Vec2d &theV);

  Naive_EXPORT Ax2d(const Naive_Ax2d_sf_t &theSF);

  const Naive_Pnt2d &Location() const { return myLoc; }

  const Naive_Vec2d &Direction() const { return myAxis; }

  void SetLocation(const Naive_Pnt2d &theP) { myLoc = theP; }

  void SetDirection(const Naive_Vec2d &theV) { myAxis = theV; }

  Naive_EXPORT Naive_Bool IsValid() const;

private:
  Naive_Pnt2d myLoc;
  Naive_Vec2d myAxis;
};

Naive_NAMESPACE_END(math);

using Naive_Ax2d = ::naivecgl::math::Ax2d;

#endif
