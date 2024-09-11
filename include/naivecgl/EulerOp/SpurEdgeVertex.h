#ifndef _NaiveCGL_EulerOp_SpurEdgeVertex_HeaderFile
#define _NaiveCGL_EulerOp_SpurEdgeVertex_HeaderFile

#include "MakeEdgeVertex.h"

Naive_NAMESPACE_BEGIN(eulerop);

class SpurEdgeVertex : public MakeEdgeVertex {
public:
  Naive_EXPORT SpurEdgeVertex();

  Naive_EXPORT SpurEdgeVertex(const Naive_Handle<topology::Vertex> &theVert,
                              const Naive_Bool theForward);

  const Naive_Handle<topology::Vertex> &GetVertex() const { return myVertex; }

  Naive_EXPORT void SetVertex(const Naive_Handle<topology::Vertex> &theVert);

  /**
   * @brief Set whether the new vertex is forward.
   *
   * @param theForward
   */
  Naive_EXPORT void SetForward(const Naive_Bool theForward);

  Naive_EXPORT void Perform() Naive_OVERRIDE;

private:
  Naive_Handle<topology::Vertex> myVertex;
  Naive_Bool myForward;
};

Naive_NAMESPACE_END(eulerop);

#endif
