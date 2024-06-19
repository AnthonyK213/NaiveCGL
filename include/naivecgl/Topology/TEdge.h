#ifndef _NaiveCGL_Topology_TEdge_HeaderFile
#define _NaiveCGL_Topology_TEdge_HeaderFile

#include "TVertex.h"

Naive_NAMESPACE_BEGIN(topology);

class TEdge final : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override {
    return Naive_Class_edge;
  }
};

Naive_NAMESPACE_END(topology);

using Naive_TEdge = ::naivecgl::topology::TEdge;
Naive_DEFINE_HANDLE(Naive_TEdge);

#endif
