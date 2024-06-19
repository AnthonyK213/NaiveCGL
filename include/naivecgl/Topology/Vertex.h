#ifndef _NaiveCGL_Topology_Vertex_HeaderFile
#define _NaiveCGL_Topology_Vertex_HeaderFile

#include "Body.h"

Naive_NAMESPACE_BEGIN(topology);

class Vertex final : public Body {
public:
  Vertex() {}
};

Naive_NAMESPACE_END(topology);

using Naive_Vertex = ::naivecgl::topology::Vertex;

namespace std {

template <> struct hash<Naive_Vertex> {
  size_t operator()(const Naive_Vertex &theBody) const {
    return ::std::hash<Naive_Body>{}(theBody);
  }
};

} // namespace std

#endif
