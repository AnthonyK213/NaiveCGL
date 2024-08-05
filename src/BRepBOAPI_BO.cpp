#include <naivecgl/BRepBOAPI/BO.h>
#include <naivecgl/Math/Precision.h>

Naive_NAMESPACE_BEGIN(brepboapi);

void BO::SetFuzzy() {
  myFuzzy = ::std::max(myFuzzy, math::Precision::Epsilon0());
}

Naive_NAMESPACE_END(brepboapi);
