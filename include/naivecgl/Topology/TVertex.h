#ifndef _NaiveCGL_Topology_TVertex_HeaderFile
#define _NaiveCGL_Topology_TVertex_HeaderFile

#include "TBody.h"

#include <naivecgl/Geometry/Point3d.h>

Naive_NAMESPACE_BEGIN(topology);

class TVertex final : public TBody {
public:
  Naive_EXPORT virtual Naive_Class Class() const override;

private:
  Naive_Point3d myPnt;
};

Naive_NAMESPACE_END(topology);

using Naive_TVertex = ::naivecgl::topology::TVertex;
Naive_DEFINE_HANDLE(Naive_TVertex);

#endif
