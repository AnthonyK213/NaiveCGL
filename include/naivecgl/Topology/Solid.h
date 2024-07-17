#ifndef _NaiveCGL_Topology_Solid_HeaderFile
#define _NaiveCGL_Topology_Solid_HeaderFile

#include "../Collection/LinkedList.h"
#include "Shell.h"

Naive_NAMESPACE_BEGIN(topology);

class Body;

class Solid final : public Naive_Topol {
public:
  Naive_EXPORT Solid();

  Naive_EXPORT Naive_Handle<Body> ParentBody() const;

  Naive_DEFINE_RTTI(Solid, Naive_Topol, Naive_Class_solid);

private:
  Naive_LinkedList<Handle_Naive_Shell> myShells;
};

Naive_NAMESPACE_END(topology);

using Naive_Solid = ::naivecgl::topology::Solid;
Naive_DEFINE_HANDLE(Naive_Solid);

#endif
