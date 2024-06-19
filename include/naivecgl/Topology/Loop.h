#ifndef _NaiveCGL_Topology_Loop_HeaderFile
#define _NaiveCGL_Topology_Loop_HeaderFile

#include "Edge.h"

Naive_NAMESPACE_BEGIN(topology);

class Loop final : public Body {
public:
  Loop() {};
};

Naive_NAMESPACE_END(topology);

using Naive_Loop = ::naivecgl::topology::Loop;

namespace std {

template <> struct hash<Naive_Loop> {
  size_t operator()(const Naive_Loop &theBody) const {
    return ::std::hash<Naive_Body>{}(theBody);
  }
};

} // namespace std

#endif
