#ifndef _NaiveCGL_EulerOp_MakeBodyFaceVertex_HeaderFile
#define _NaiveCGL_EulerOp_MakeBodyFaceVertex_HeaderFile

#include "Operator.h"

Naive_NAMESPACE_BEGIN(eulerop);

class MakeBodyFaceVertex : public Operator {
public:
  Naive_EXPORT MakeBodyFaceVertex();

  Naive_EXPORT void Perform() Naive_OVERRIDE;

  Naive_EXPORT Naive_Handle<topology::Body> NewBody() const;

  Naive_EXPORT Naive_Handle<topology::Face> NewFace() const;

  Naive_EXPORT Naive_Handle<topology::Vertex> NewVertex() const;

  Naive_DEFINE_EO(MakeBodyFaceVertex);
};

Naive_NAMESPACE_END(eulerop);

#endif
