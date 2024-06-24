#ifndef _NaiveCGL_Math_Rect_HeaderFile
#define _NaiveCGL_Math_Rect_HeaderFile

#include "Ax2.h"
#include "Intv.h"

Naive_NAMESPACE_BEGIN(math);

class Rect final {
public:
private:
  Naive_Ax2 myAx2;
  Naive_Intv myXIntv;
  Naive_Intv myYIntv;
};

Naive_NAMESPACE_END(math);

using Naive_Rect = ::naivecgl::math::Rect;

#endif
