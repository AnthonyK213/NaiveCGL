#include <naivecgl/BndShape/EnclosingDisc.h>

Naive_NAMESPACE_BEGIN(bndshape);

void EnclosingDisc::ReBuild(const Naive_Point2dList &thePoints) {}

Naive_Bool EnclosingDisc::Circle(Naive_Point2d &theOrigin, Naive_Real &theR) {
  if (!theOrigin.IsValid())
    return false;

  return true;
}

Naive_NAMESPACE_END(bndshape);
