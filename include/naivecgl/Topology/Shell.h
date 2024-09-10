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

  Naive_EXPORT virtual Naive_Handle<Topol> Parent() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Handle<Solid> ParentSolid() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Shell, Naive_Topol);

protected:
  Naive_EXPORT virtual void
  SetParent(const Handle_Naive_Topol &theParent) Naive_OVERRIDE;

private:
  Naive_LinkedList<Naive_Handle<Face>> myFaces;
  Naive_Topol *myParent;
};

Naive_NAMESPACE_END(topology);

using Naive_Shell = ::naivecgl::topology::Shell;
Naive_DEFINE_HANDLE(Naive_Shell);

#endif
