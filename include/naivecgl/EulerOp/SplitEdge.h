#ifndef _NaiveCGL_EulerOp_SplitEdge_HeaderFile
#define _NaiveCGL_EulerOp_SplitEdge_HeaderFile

#include "MakeEdgeVertex.h"

Naive_NAMESPACE_BEGIN(euler_op);

class SplitEdge : public MakeEdgeVertex {
public:
  Naive_EXPORT SplitEdge();

  Naive_EXPORT SplitEdge(const Naive_Handle<topology::Edge> &theEdge,
                         const Naive_Bool theForward);

  const Naive_Handle<topology::Edge> &GetEdge() const { return myEdge; }

  const Naive_Bool GetForward() const { return myForward; }

  Naive_EXPORT void SetEdge(const Naive_Handle<topology::Edge> &theEdge);

  /**
   * @brief Set which vertex of the edge to be split.
   *
   * @param theForward
   */
  Naive_EXPORT void SetForward(const Naive_Bool theForward);

protected:
  Naive_EXPORT virtual Naive_Code CheckParams() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code PerformInternal() Naive_OVERRIDE;

private:
  Naive_Handle<topology::Edge> myEdge;
  Naive_Bool myForward;
};

Naive_NAMESPACE_END(euler_op);

#endif
