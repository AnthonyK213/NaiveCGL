#ifndef _NaiveCGL_Topology_Fin_HeaderFile
#define _NaiveCGL_Topology_Fin_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Loop;
class Edge;

class Fin final : public Naive_Topol {
public:
  Naive_EXPORT Fin();

  Naive_EXPORT Naive_Handle<Loop> ParentLoop() const;

  Naive_EXPORT Naive_Handle<Edge> ParentEdge() const;

  Naive_EXPORT Naive_Handle<Fin> Prev() const { return myPrev; }

  Naive_EXPORT Naive_Handle<Fin> Next() const { return myNext; }

  Naive_EXPORT Naive_Handle<Fin> Twin() const { return myTwin; }

  Naive_DEFINE_RTTI(Fin, Naive_Topol);

private:
  Edge *myEdge;
  Fin *myPrev;
  Fin *myNext;
  Fin *myTwin; /* Next fin around myEdge. */
};

Naive_NAMESPACE_END(topology);

using Naive_Fin = ::naivecgl::topology::Fin;
Naive_DEFINE_HANDLE(Naive_Fin);

#endif
