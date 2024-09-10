#ifndef _NaiveCGL_Topology_Loop_HeaderFile
#define _NaiveCGL_Topology_Loop_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Face;
class Fin;

class Loop final : public Naive_Topol {
public:
  Naive_EXPORT Loop();

  Naive_EXPORT virtual Naive_Handle<Topol> Parent() const Naive_OVERRIDE;

  Naive_Handle<Face> ParentFace() const;

  Naive_DEFINE_RTTI(Loop, Naive_Topol);

private:
  Face *myFace;
  Fin *myFin;
  Naive_Loop_type myType;
};

Naive_NAMESPACE_END(topology);

using Naive_Loop = ::naivecgl::topology::Loop;
Naive_DEFINE_HANDLE(Naive_Loop);

#endif
