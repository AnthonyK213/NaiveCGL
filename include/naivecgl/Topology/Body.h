#ifndef _NaiveCGL_Topology_Body_HeaderFile
#define _NaiveCGL_Topology_Body_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Body final : public Naive_Topol {
public:
  Naive_EXPORT Body();

  Naive_EXPORT virtual Naive_Class Class() const Naive_OVERRIDE;

private:
  Naive_LinkedList<Handle_Naive_Topol> myChildren;
};

Naive_NAMESPACE_END(topology);

using Naive_Body = ::naivecgl::topology::Body;
Naive_DEFINE_HANDLE(Naive_Body);

#endif
