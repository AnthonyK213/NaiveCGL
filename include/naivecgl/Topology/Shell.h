#ifndef _NaiveCGL_Topology_Shell_HeaderFile
#define _NaiveCGL_Topology_Shell_HeaderFile

#include "../Collection/LinkedList.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Solid;
class Face;

class Shell final : public Naive_Topol {
  friend class eulerop::MakeBodyFaceVertex;

public:
  Naive_EXPORT Shell();

  Naive_EXPORT Naive_Handle<Solid> ParentShell() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Shell, Naive_Topol);

private:
  Naive_LinkedList<Naive_Handle<Face>> myFaces;
};

Naive_NAMESPACE_END(topology);

using Naive_Shell = ::naivecgl::topology::Shell;
Naive_DEFINE_HANDLE(Naive_Shell);

#endif
