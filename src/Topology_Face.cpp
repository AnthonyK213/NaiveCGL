#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Shell.h>

Naive_NAMESPACE_BEGIN(topology);

Face::Face() : Naive_Topol() {}

Naive_Class Face::Class() const { return Naive_Class_face; }

Shell *Face::ParentShell() const { return dynamic_cast<Shell *>(myParent); }

Naive_NAMESPACE_END(topology);
