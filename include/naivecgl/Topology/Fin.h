#ifndef _NaiveCGL_Topology_Fin_HeaderFile
#define _NaiveCGL_Topology_Fin_HeaderFile

#include "Edge.h"

Naive_NAMESPACE_BEGIN(topology);

class Fin final : public Body {
public:
  Fin() {}
};

Naive_NAMESPACE_END(topology);

using Naive_Fin = ::naivecgl::topology::Fin;

namespace std {

template <> struct hash<Naive_Fin> {
  size_t operator()(const Naive_Fin &theBody) const {
    return ::std::hash<Naive_Body>{}(theBody);
  }
};

} // namespace std

#endif
