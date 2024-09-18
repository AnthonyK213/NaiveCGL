#ifndef _NaiveCGL_EulerOp_MakeEdgeVertex_HeaderFile
#define _NaiveCGL_EulerOp_MakeEdgeVertex_HeaderFile

#include "Operator.h"

Naive_NAMESPACE_BEGIN(euler_op);

class MakeEdgeVertex : public Operator {
public:
  Naive_EXPORT Naive_Handle<topology::Vertex> NewVertex() const;

  Naive_EXPORT Naive_Handle<topology::Edge> NewEdge() const;

  Naive_DEFINE_EO(MakeEdgeVertex);

protected:
  Naive_EXPORT MakeEdgeVertex();
};

Naive_NAMESPACE_END(euler_op);

#endif
