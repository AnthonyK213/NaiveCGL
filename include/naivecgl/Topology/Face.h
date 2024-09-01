#ifndef _NaiveCGL_Topology_Face_HeaderFile
#define _NaiveCGL_Topology_Face_HeaderFile

#include "../Collection/LinkedList.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(geometry);

class Surface;

Naive_NAMESPACE_END(geometry);

Naive_NAMESPACE_BEGIN(topology);

class Shell;
class Loop;

class Face final : public Naive_Topol {
public:
  Naive_EXPORT Face();

  Naive_EXPORT Naive_Handle<Shell> ParentShell() const;

  Naive_DEFINE_RTTI(Face, Naive_Topol);

private:
  Naive_Real myTol;
  Naive_Handle<geometry::Surface> mySrf;
  Naive_LinkedList<Naive_Handle<Loop>> myLoops;
};

Naive_NAMESPACE_END(topology);

using Naive_Face = ::naivecgl::topology::Face;
Naive_DEFINE_HANDLE(Naive_Face);

#endif
