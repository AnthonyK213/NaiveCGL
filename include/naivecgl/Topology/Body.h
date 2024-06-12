#ifndef _NaiveCGL_Topology_Body_HeaderFile
#define _NaiveCGL_Topology_Body_HeaderFile

#include "Shell.h"

Naive_NAMESPACE_BEGIN(topology);

class Body : public Naive_Transient {};

Naive_NAMESPACE_END(topology);

using Naive_Body = ::naivecgl::topology::Body;
Naive_DEFINE_HANDLE(Naive_Body);

#endif
