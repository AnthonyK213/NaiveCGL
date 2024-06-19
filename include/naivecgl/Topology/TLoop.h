#ifndef _NaiveCGL_Topology_TLoop_HeaderFile
#define _NaiveCGL_Topology_TLoop_HeaderFile

#include "TEdge.h"

Naive_NAMESPACE_BEGIN(topology);

class TLoop final : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override {
    return Naive_Class_loop;
  }
};

Naive_NAMESPACE_END(topology);

using Naive_TLoop = ::naivecgl::topology::TLoop;
Naive_DEFINE_HANDLE(Naive_TLoop);

#endif
