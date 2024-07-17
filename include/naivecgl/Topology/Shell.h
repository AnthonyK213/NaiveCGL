#ifndef _NaiveCGL_Topology_Shell_HeaderFile
#define _NaiveCGL_Topology_Shell_HeaderFile

#include "../Collection/LinkedList.h"
#include "Face.h"

Naive_NAMESPACE_BEGIN(topology);

class Solid;

class Shell final : public Naive_Topol {
public:
  Naive_EXPORT Shell();

  Naive_EXPORT Naive_Handle<Solid> ParentShell() const;

  Naive_DEFINE_RTTI(Shell, Naive_Topol, Naive_Class_shell);

private:
  Naive_LinkedList<Handle_Naive_Face> myFaces;
};

Naive_NAMESPACE_END(topology);

using Naive_Shell = ::naivecgl::topology::Shell;
Naive_DEFINE_HANDLE(Naive_Shell);

#endif
