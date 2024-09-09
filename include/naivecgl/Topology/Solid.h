#ifndef _NaiveCGL_Topology_Solid_HeaderFile
#define _NaiveCGL_Topology_Solid_HeaderFile

#include "../Collection/LinkedList.h"
#include "../Math/Box.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Body;
class Shell;

class Solid final : public Naive_Topol {
public:
  Naive_EXPORT Solid();

  Naive_EXPORT Naive_Handle<Body> ParentBody() const;

  Naive_DEFINE_RTTI(Solid, Naive_Topol);

protected:
  Naive_EXPORT virtual void UpdateBox(math::Box *theBox) Naive_OVERRIDE;

private:
  Naive_LinkedList<Naive_Handle<Shell>> myShells;
  Naive_Box myBox;
};

Naive_NAMESPACE_END(topology);

using Naive_Solid = ::naivecgl::topology::Solid;
Naive_DEFINE_HANDLE(Naive_Solid);

#endif
