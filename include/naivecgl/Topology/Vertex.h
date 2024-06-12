#ifndef _NaiveCGL_Topology_Vertex_HeaderFile
#define _NaiveCGL_Topology_Vertex_HeaderFile

#include <naivecgl/Common/Handle.h>
#include <naivecgl/Geometry/Point3d.h>

Naive_NAMESPACE_BEGIN(topology);

class Vertex final : public Naive_Transient {};

Naive_NAMESPACE_END(topology);

using Naive_Vertex = ::naivecgl::topology::Vertex;
Naive_DEFINE_HANDLE(Naive_Vertex);

#endif
