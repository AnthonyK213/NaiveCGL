#ifndef _NaiveCGL_Topology_TCompound_HeaderFile
#define _NaiveCGL_Topology_TCompound_HeaderFile

#include "TSolid.h"

Naive_NAMESPACE_BEGIN(topology);

class TCompound final : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override {
    return Naive_Class_compound;
  }
};

Naive_NAMESPACE_END(topology);

using Naive_TCompound = ::naivecgl::topology::TCompound;
Naive_DEFINE_HANDLE(Naive_TCompound);

#endif
