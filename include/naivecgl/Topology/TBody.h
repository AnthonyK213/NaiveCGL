#ifndef _NaiveCGL_Topology_TBody_HeaderFile
#define _NaiveCGL_Topology_TBody_HeaderFile

#include <naivecgl/Common/Handle.h>

Naive_NAMESPACE_BEGIN(topology);

class Body;

class TBody : public Naive_Transient {
public:
  Naive_EXPORT virtual Naive_Class Class() const = 0;

private:
  Naive_LinkedList<Body> myBodies;
};

Naive_NAMESPACE_END(topology);

using Naive_TBody = ::naivecgl::topology::TBody;
Naive_DEFINE_HANDLE(Naive_TBody);

#endif
