#ifndef _NaiveCGL_EulerOp_MakeFaceEdge_HeaderFile
#define _NaiveCGL_EulerOp_MakeFaceEdge_HeaderFile

#include "Operator.h"

Naive_NAMESPACE_BEGIN(euler_op);

class MakeFaceEdge : public Operator {
public:
  Naive_EXPORT MakeFaceEdge();

  Naive_EXPORT MakeFaceEdge(const Naive_Handle<topology::Loop> &theLoop,
                            const Naive_Handle<topology::Fin> &theFin1,
                            const Naive_Handle<topology::Fin> &theFin2);

  const Naive_Handle<topology::Loop> &GetLoop() const { return myLoop; }

  const Naive_Handle<topology::Fin> &GetFin1() const { return myFin1; }

  const Naive_Handle<topology::Fin> &GetFin2() const { return myFin2; }

  Naive_EXPORT void SetLoop(const Naive_Handle<topology::Loop> &theLoop);

  Naive_EXPORT void SetFin1(const Naive_Handle<topology::Fin> &theFin);

  Naive_EXPORT void SetFin2(const Naive_Handle<topology::Fin> &theFin);

  Naive_EXPORT Naive_Handle<topology::Face> NewFace() const;

  Naive_EXPORT Naive_Handle<topology::Edge> NewEdge() const;

  Naive_DEFINE_EO(MakeFaceEdge);

protected:
  Naive_EXPORT virtual Naive_Code CheckParams() const Naive_OVERRIDE;

  Naive_EXPORT virtual Naive_Code PerformInternal() Naive_OVERRIDE;

private:
  Naive_Handle<topology::Loop> myLoop;
  Naive_Handle<topology::Fin> myFin1;
  Naive_Handle<topology::Fin> myFin2;
};

Naive_NAMESPACE_END(euler_op);

#endif
