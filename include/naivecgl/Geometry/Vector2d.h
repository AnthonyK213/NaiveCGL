#ifndef _NaiveCGL_Geometry_Vector2d_HeaderFile
#define _NaiveCGL_Geometry_Vector2d_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(geometry);

class Vector2d final {
public:
  Naive_EXPORT Vector2d();

  Naive_EXPORT Vector2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Vector2d(const Naive_Vector2d_t &theVec);

  Naive_EXPORT Vector2d(const Naive_XY &theXY);

  Naive_EXPORT const Naive_XY &XY() const { return myXY; }

  Naive_EXPORT Naive_XY &ChangeXY() { return myXY; }

  Naive_EXPORT Naive_Real X() const { return myXY.x(); }

  Naive_EXPORT Naive_Real Y() const { return myXY.y(); }

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT static const Vector2d &Unset();

  Naive_EXPORT Naive_Bool Dump(Naive_Vector2d_t &theV) const;

private:
  Naive_XY myXY;
};

Naive_NAMESPACE_END(geometry);

using Naive_Vector2d = ::naivecgl::geometry::Vector2d;
using Naive_Vector2dList = Naive_List<Naive_Vector2d>;
using Naive_Vector2dList2 = Naive_List2<Naive_Vector2d>;

#endif
