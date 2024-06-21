#ifndef _NaiveCGL_Topology_Edge_HeaderFile
#define _NaiveCGL_Topology_Edge_HeaderFile

#include "../Geometry/Curve.h"
#include "Vertex.h"

Naive_NAMESPACE_BEGIN(topology);

class Fin;

class Edge final : public Naive_Topol {
public:
  Naive_EXPORT Edge();

  Naive_EXPORT virtual Naive_Class Class() const Naive_OVERRIDE;

  Naive_EXPORT Fin *ParentFin() const;

private:
  Handle_Naive_Curve myCrv;
  Naive_Vertex myVerts[2];
};

Naive_NAMESPACE_END(topology);

using Naive_Edge = ::naivecgl::topology::Edge;
Naive_DEFINE_HANDLE(Naive_Edge);

#endif
