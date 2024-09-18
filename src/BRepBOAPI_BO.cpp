#include <naivecgl/BRepBOAPI/BO.h>
#include <naivecgl/Math/Precision.h>

Naive_NAMESPACE_BEGIN(brep_bo_api);

void BO::SetFuzzy() {
  myFuzzy = ::std::max(myFuzzy, math::Precision::Epsilon0());
}

Naive_NAMESPACE_END(brep_bo_api);
