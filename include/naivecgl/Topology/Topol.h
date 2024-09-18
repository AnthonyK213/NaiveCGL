#ifndef _NaiveCGL_Topology_Topol_HeaderFile
#define _NaiveCGL_Topology_Topol_HeaderFile

#include "../Common/ClassType.h"
#include "Location.h"

Naive_NAMESPACE_BEGIN(math);

class Box;

Naive_NAMESPACE_END(math);

Naive_NAMESPACE_BEGIN(euler_op);

class MakeBodyFaceVertex;
class MakeEdgeKillLoop;
class MakeEdgeVertex;
class MakeFaceEdge;
class MakeGenusBody;
class SplitEdge;
class SpurEdgeVertex;

Naive_NAMESPACE_END(euler_op);

Naive_NAMESPACE_BEGIN(topology);

class Topol : public Naive_Object {
  friend class euler_op::MakeBodyFaceVertex;
  friend class euler_op::MakeEdgeKillLoop;
  friend class euler_op::MakeEdgeVertex;
  friend class euler_op::MakeFaceEdge;
  friend class euler_op::MakeGenusBody;
  friend class euler_op::SplitEdge;
  friend class euler_op::SpurEdgeVertex;

public:
  Topol(const Topol &theOther) Naive_DELETE;

  Naive_EXPORT virtual Topol *Parent() const;

  Naive_EXPORT virtual Topol *TopTopol() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox);

  Naive_EXPORT virtual Naive_Bool IsManifold() const;

  Naive_DEFINE_RTTI(Topol, Naive_Object);

protected:
  Naive_EXPORT Topol();

  Naive_EXPORT virtual void SetParent(Topol *theParent);
};

Naive_NAMESPACE_END(topology);

using Naive_Topol = ::naivecgl::topology::Topol;
Naive_DEFINE_HANDLE(Naive_Topol);

#endif
