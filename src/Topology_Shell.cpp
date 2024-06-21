#include <naivecgl/Topology/Shell.h>
#include <naivecgl/Topology/Solid.h>

Naive_NAMESPACE_BEGIN(topology);

Shell::Shell() : Naive_Topol() {}

Naive_Class Shell::Class() const { return Naive_Class_shell; }

Solid *Shell::ParentShell() const { return dynamic_cast<Solid *>(myParent); }

Naive_NAMESPACE_END(topology);
