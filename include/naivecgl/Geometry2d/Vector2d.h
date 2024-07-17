#ifndef _NaiveCGL_Geometry_Vector2d_HeaderFile
#define _NaiveCGL_Geometry_Vector2d_HeaderFile

#include "../Math/Vec2d.h"
#include "Geometry.h"

Naive_NAMESPACE_BEGIN(geometry2d);

class Vector2d final : public Naive_Geometry2d {
public:
  Naive_EXPORT Vector2d();

  Naive_EXPORT Vector2d(const Naive_Real theX, const Naive_Real theY);

  Naive_EXPORT Vector2d(const Naive_Vec2d &theVec);

  Naive_EXPORT const Naive_Vec2d &Vec2d() const { return myVec2d; }

  Naive_EXPORT Naive_Real X() const { return myVec2d.X(); }

  Naive_EXPORT Naive_Real Y() const { return myVec2d.Y(); }

  Naive_EXPORT virtual Naive_Bool IsValid() const Naive_OVERRIDE;

  Naive_EXPORT virtual Handle_Naive_Geometry2d Clone() const Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Vector2d, Naive_Geometry2d);

private:
  Naive_Vec2d myVec2d;
};

Naive_NAMESPACE_END(geometry2d);

using Naive_Vector2d = ::naivecgl::geometry2d::Vector2d;
Naive_DEFINE_HANDLE(Naive_Vector2d);
using Naive_Vector2dList1 = Naive_List1<Handle_Naive_Vector2d>;
using Naive_Vector2dList2 = Naive_List2<Handle_Naive_Vector2d>;

#endif
