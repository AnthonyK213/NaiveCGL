#ifndef _NaiveCGL_Topology_Loop_HeaderFile
#define _NaiveCGL_Topology_Loop_HeaderFile

#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Face;
class Fin;

class Loop final : public Naive_Topol {
public:
  Naive_EXPORT Loop();

  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT Face *ParentFace() const;

  Naive_Loop_type Type() const { return myType; }

  Naive_EXPORT Naive_Bool IsTopologicalClosed() const;

  Naive_EXPORT Naive_Code AppendFin(Fin *theFin);

  Naive_EXPORT Naive_Code RemoveFin(Fin *theFin);

  Naive_DEFINE_RTTI(Loop, Naive_Topol);

private:
  Face *myFace; /* Parent face. */
  Fin *myFin;   /* Head of fins in the loop. */
  Naive_Loop_type myType;
};

Naive_NAMESPACE_END(topology);

using Naive_Loop = ::naivecgl::topology::Loop;
Naive_DEFINE_HANDLE(Naive_Loop);

#endif
