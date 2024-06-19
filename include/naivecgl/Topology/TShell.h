#ifndef _NaiveCGL_Topology_TShell_HeaderFile
#define _NaiveCGL_Topology_TShell_HeaderFile

#include "TFace.h"

Naive_NAMESPACE_BEGIN(topology);

class TShell final : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override {
    return Naive_Class_shell;
  }
};

Naive_NAMESPACE_END(topology);

using Naive_TShell = ::naivecgl::topology::TShell;
Naive_DEFINE_HANDLE(Naive_TShell);

#endif
