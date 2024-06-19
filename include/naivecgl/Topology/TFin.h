#ifndef _NaiveCGL_Topology_TFin_HeaderFile
#define _NaiveCGL_Topology_TFin_HeaderFile

#include "TEdge.h"

Naive_NAMESPACE_BEGIN(topology);

class TFin final : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override {
    return Naive_Class_fin;
  }
};

Naive_NAMESPACE_END(topology);

using Naive_TFin = ::naivecgl::topology::TFin;
Naive_DEFINE_HANDLE(Naive_TFin);

#endif
