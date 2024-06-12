#ifndef _NaiveCGL_Topology_Loop_HeaderFile
#define _NaiveCGL_Topology_Loop_HeaderFile

#include "Edge.h"

Naive_NAMESPACE_BEGIN(topology);

class Loop final : public Naive_Transient {};

Naive_NAMESPACE_END(topology);

using Naive_Loop = ::naivecgl::topology::Loop;
Naive_DEFINE_HANDLE(Naive_Loop);

#endif
