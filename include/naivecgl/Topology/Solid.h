#ifndef _NaiveCGL_Topology_Solid_HeaderFile
#define _NaiveCGL_Topology_Solid_HeaderFile

#include "Shell.h"

Naive_NAMESPACE_BEGIN(topology);

class Body;

class Solid final : public Naive_Topol {
public:
  Naive_EXPORT Solid();

  Naive_EXPORT virtual Naive_Class Class() const Naive_OVERRIDE;

  Naive_EXPORT Body *ParentBody() const;
};

Naive_NAMESPACE_END(topology);

using Naive_Solid = ::naivecgl::topology::Solid;
Naive_DEFINE_HANDLE(Naive_Solid);

#endif
