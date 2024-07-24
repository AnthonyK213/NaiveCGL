#ifndef _NaiveCGL_Math_Ax22d_HeaderFile
#define _NaiveCGL_Math_Ax22d_HeaderFile

#include "Pnt2d.h"
#include "Vec2d.h"

Naive_NAMESPACE_BEGIN(math);

class Ax22d final {
public:
  Naive_EXPORT Ax22d();

  Naive_EXPORT Ax22d(const Naive_Pnt2d &theP, const Naive_Vec2d &theVx,
                     const Naive_Vec2d &theVy);

  Naive_EXPORT Ax22d(const Naive_Pnt2d &theP, const Naive_Vec2d &theV,
                     const Naive_Bool &theIsSense = Naive_True);

  const Naive_Pnt2d &Location() const { return myLoc; }

  const Naive_Vec2d &XDirection() const { return myXDir; }

  const Naive_Vec2d &YDirection() const { return myYDir; }

  void SetLocation(const Naive_Pnt2d &theP) { myLoc = theP; }

  Naive_EXPORT void SetXDirection(const Naive_Vec2d &theV);

  Naive_EXPORT void SetYDirection(const Naive_Vec2d &theV);

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool Dump(Naive_Ax22d_sf_t &theAx22d) const;

private:
  Naive_Pnt2d myLoc;
  Naive_Vec2d myXDir;
  Naive_Vec2d myYDir;
};

Naive_NAMESPACE_END(math);

using Naive_Ax22d = ::naivecgl::math::Ax22d;

#endif
