#ifndef _NaiveCGL_EulerOp_MakeBodyFaceVertex_HeaderFile
#define _NaiveCGL_EulerOp_MakeBodyFaceVertex_HeaderFile

#include "Operator.h"

Naive_NAMESPACE_BEGIN(euler_op);

class MakeBodyFaceVertex : public Operator {
public:
  Naive_EXPORT MakeBodyFaceVertex();

  Naive_EXPORT Naive_Handle<topology::Body> NewBody() const;

  Naive_EXPORT Naive_Handle<topology::Face> NewFace() const;

  Naive_EXPORT Naive_Handle<topology::Vertex> NewVertex() const;

  Naive_DEFINE_EO(MakeBodyFaceVertex);

protected:
  Naive_EXPORT virtual Naive_Code PerformInternal() Naive_OVERRIDE;
};

Naive_NAMESPACE_END(euler_op);

#endif
