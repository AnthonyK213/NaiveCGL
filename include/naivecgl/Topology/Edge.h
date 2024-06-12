#ifndef _NaiveCGL_Topology_Edge_HeaderFile
#define _NaiveCGL_Topology_Edge_HeaderFile

#include "Vertex.h"

Naive_NAMESPACE_BEGIN(topology);

class Edge final : public Naive_Transient {};

Naive_NAMESPACE_END(topology);

using Naive_Edge = ::naivecgl::topology::Edge;
Naive_DEFINE_HANDLE(Naive_Edge);

#endif
