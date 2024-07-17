#ifndef _NaiveCGL_Topology_Face_HeaderFile
#define _NaiveCGL_Topology_Face_HeaderFile

#include "../Collection/LinkedList.h"
#include "../Geometry/Surface.h"
#include "Loop.h"

Naive_NAMESPACE_BEGIN(topology);

class Shell;

class Face final : public Naive_Topol {
public:
  Naive_EXPORT Face();

  Naive_EXPORT Naive_Handle<Shell> ParentShell() const;

  Naive_DEFINE_RTTI(Face, Naive_Topol, Naive_Class_face);

private:
  Naive_Real myTol;
  Handle_Naive_Surface mySrf;
  Naive_LinkedList<Handle_Naive_Loop> myLoops;
};

Naive_NAMESPACE_END(topology);

using Naive_Face = ::naivecgl::topology::Face;
Naive_DEFINE_HANDLE(Naive_Face);

#endif
