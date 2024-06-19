#ifndef _NaiveCGL_Topology_TSolid_HeaderFile
#define _NaiveCGL_Topology_TSolid_HeaderFile

#include "TShell.h"

Naive_NAMESPACE_BEGIN(topology);

class TSolid : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override {
    return Naive_Class_solid;
  }
};

Naive_NAMESPACE_END(topology);

using Naive_TSolid = ::naivecgl::topology::TSolid;
Naive_DEFINE_HANDLE(Naive_TSolid);

#endif
