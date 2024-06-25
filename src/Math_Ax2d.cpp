#include <naivecgl/Math/Ax2d.h>

Naive_NAMESPACE_BEGIN(math);

Ax2d::Ax2d() : myLoc(), myAxis() {}

Ax2d::Ax2d(const Naive_Pnt2d &theP, const Naive_Vec2d &theV)
    : myLoc(theP), myAxis(theV.Normalized()) {}

Naive_Bool Ax2d::IsValid() const { return myLoc.IsValid() && myAxis.IsValid(); }

Naive_NAMESPACE_END(math);
