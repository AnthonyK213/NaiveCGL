#ifndef _NaiveCGL_Topology_TFace_HeaderFile
#define _NaiveCGL_Topology_TFace_HeaderFile

#include "TLoop.h"

Naive_NAMESPACE_BEGIN(topology);

class TFace final : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override {
    return Naive_Class_face;
  }
};

Naive_NAMESPACE_END(topology);

using Naive_TFace = ::naivecgl::topology::TFace;
Naive_DEFINE_HANDLE(Naive_TFace);

#endif
