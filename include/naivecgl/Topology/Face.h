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
  friend class Shell;
  friend class euler_op::MakeBodyFaceVertex;
  friend class euler_op::MakeFaceEdge;

public:
  Naive_EXPORT Face();

  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT Shell *ParentShell() const;

  Naive_EXPORT Naive_Handle<Loop> OuterLoop() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Face, Naive_Topol);

protected:
  Naive_EXPORT virtual void SetParent(Naive_Topol *theParent) Naive_OVERRIDE;

private:
  Naive_LinkedList<Naive_Handle<Loop>> myLoops;
  Shell *myShell;            /* Parent shell. */
  Face *myPrev;              /* Previous face in myShell. */
  Naive_Handle<Face> myNext; /* Next face in myShell. */
  Naive_Handle<geometry::Surface> mySrf;
  Naive_Box myBox;
  Naive_Real myTol;
};

Naive_NAMESPACE_END(topology);

using Naive_Face = ::naivecgl::topology::Face;
Naive_DEFINE_HANDLE(Naive_Face);

#endif
