#ifndef _NaiveCGL_Topology_Fin_HeaderFile
#define _NaiveCGL_Topology_Fin_HeaderFile

#include "Edge.h"

Naive_NAMESPACE_BEGIN(topology);

class Loop;

class Fin final : public Naive_Topol {
public:
  Naive_EXPORT Fin();

  Naive_EXPORT Naive_Handle<Loop> ParentLoop() const;

  Naive_EXPORT Handle_Naive_Edge Edge() const { return myEdge; }

  Naive_EXPORT Naive_Handle<Fin> Prev() const { return myPrev; }

  Naive_EXPORT Naive_Handle<Fin> Next() const { return myNext; }

  Naive_EXPORT Naive_Handle<Fin> Twin() const { return myTwin; }

  Naive_DEFINE_RTTI(Fin, Naive_Topol, Naive_Class_fin);

private:
  Handle_Naive_Edge myEdge;
  Fin *myPrev;
  Fin *myNext;
  Fin *myTwin; /* Twin when manifold; Next neighbor when non-manifold. */
};

Naive_NAMESPACE_END(topology);

using Naive_Fin = ::naivecgl::topology::Fin;
Naive_DEFINE_HANDLE(Naive_Fin);

#endif
