#ifndef _NaiveCGL_Topology_Vertex_HeaderFile
#define _NaiveCGL_Topology_Vertex_HeaderFile

#include "../Math/Pnt3d.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Edge;

class Vertex final : public Naive_Topol {
public:
  Naive_EXPORT Vertex();

  Naive_EXPORT virtual Naive_Class Class() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Handle<Edge> ParentEdge() const;

private:
  Naive_Real myTol;
  Naive_Pnt3d myPnt;
};

Naive_NAMESPACE_END(topology);

using Naive_Vertex = ::naivecgl::topology::Vertex;
Naive_DEFINE_HANDLE(Naive_Vertex);

#endif
