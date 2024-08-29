#ifndef _NaiveCGL_EulerOp_Operator_HeaderFile
#define _NaiveCGL_EulerOp_Operator_HeaderFile

#include "../Common/Command.h"

Naive_NAMESPACE_BEGIN(eulerop);

class TEV;

class Operator : common::Command {
public:
  Naive_EXPORT virtual const TEV &GetTEV() const = 0;

protected:
};

#define Naive_DEFINE_EO(Op_)                                                   \
public:                                                                        \
  Naive_EXPORT static const TEV &get_TEV();                                    \
  Naive_EXPORT virtual const TEV &GetTEV() const Naive_OVERRIDE;

#define Naive_IMPLEMENT_EO(Op_, ...)                                           \
  const TEV &Op_::GetTEV() const { return Op_::get_TEV(); }                    \
  const TEV &Op_::get_TEV() {                                                  \
    static TEV aTEV{__VA_ARGS__};                                              \
    return aTEV;                                                               \
  }

Naive_NAMESPACE_END(eulerop);

#endif
