#ifndef _NaiveCGL_Topology_Shell_HeaderFile
#define _NaiveCGL_Topology_Shell_HeaderFile

#include "Face.h"

Naive_NAMESPACE_BEGIN(topology);

class Shell final : public Naive_Transient {};

Naive_NAMESPACE_END(topology);

using Naive_Shell = ::naivecgl::topology::Shell;
Naive_DEFINE_HANDLE(Naive_Shell);

#endif
