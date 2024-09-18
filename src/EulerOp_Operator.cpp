#include <naivecgl/EulerOp/Operator.h>

Naive_NAMESPACE_BEGIN(euler_op);

Naive_Code Operator::CheckParams() const { return Naive_Code_ok; }

void Operator::Perform() {
  if (Status() != Naive_Code_initialized)
    return;

  SetStatus(CheckParams());
  if (Status() != Naive_Code_ok)
    return;

  SetStatus(PerformInternal());
}

Naive_NAMESPACE_END(euler_op);
