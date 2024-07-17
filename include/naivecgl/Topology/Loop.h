#ifndef _NaiveCGL_Topology_Loop_HeaderFile
#define _NaiveCGL_Topology_Loop_HeaderFile

#include "../Collection/LinkedList.h"
#include "Fin.h"

Naive_NAMESPACE_BEGIN(topology);

class Face;

class Loop final : public Naive_Topol {
public:
  Naive_EXPORT Loop();

  Naive_EXPORT Naive_Handle<Face> ParentFace() const;

  Naive_DEFINE_RTTI(Loop, Naive_Topol);

private:
  Naive_LinkedList<Handle_Naive_Fin> myFins;
  Naive_Loop_type myType;
};

Naive_NAMESPACE_END(topology);

using Naive_Loop = ::naivecgl::topology::Loop;
Naive_DEFINE_HANDLE(Naive_Loop);

#endif
