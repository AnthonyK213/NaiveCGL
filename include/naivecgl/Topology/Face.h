#ifndef _NaiveCGL_Topology_Face_HeaderFile
#define _NaiveCGL_Topology_Face_HeaderFile

#include "../Collection/LinkedList.h"
#include "../Math/Box.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Surface;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Shell;
class Loop;

class Face final : public Naive_Topol {
  friend class eulerop::MakeBodyFaceVertex;

public:
  Naive_EXPORT Face();

  Naive_EXPORT virtual Naive_Handle<Topol> Parent() const Naive_OVERRIDE;

  Naive_EXPORT Naive_Handle<Shell> ParentShell() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Face, Naive_Topol);

protected:
  Naive_EXPORT virtual void
  SetParent(const Handle_Naive_Topol &theParent) Naive_OVERRIDE;

private:
  Shell *myShell;
  Naive_LinkedList<Naive_Handle<Loop>> myLoops;
  Naive_Handle<geometry::Surface> mySrf;
  Naive_Box myBox;
  Naive_Real myTol;
};

Naive_NAMESPACE_END(topology);

using Naive_Face = ::naivecgl::topology::Face;
Naive_DEFINE_HANDLE(Naive_Face);

#endif
