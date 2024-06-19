#ifndef _NaiveCGL_Topology_Location_HeaderFile
#define _NaiveCGL_Topology_Location_HeaderFile

#include <naivecgl/Geometry/Transform3d.h>

Naive_NAMESPACE_BEGIN(topology);

class Location final {
public:
  Location() {};

  void Clear();

  Naive_Bool operator==(const Location &theOther) const {
    // TODO: Implementation.
    return Naive_True;
  }

private:
};

Naive_NAMESPACE_END(topology);

using Naive_Location = ::naivecgl::topology::Location;

#endif
