#ifndef _NaiveCGL_Topology_Face_HeaderFile
#define _NaiveCGL_Topology_Face_HeaderFile

#include "Loop.h"

Naive_NAMESPACE_BEGIN(topology);

class Face final : public Naive_Transient {};

Naive_NAMESPACE_END(topology);

using Naive_Face = ::naivecgl::topology::Face;
Naive_DEFINE_HANDLE(Naive_Face);

#endif
