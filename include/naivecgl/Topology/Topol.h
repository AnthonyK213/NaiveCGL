#ifndef _NaiveCGL_Topology_Topol_HeaderFile
#define _NaiveCGL_Topology_Topol_HeaderFile

#include "../Common/ClassType.h"
#include "Location.h"

Naive_NAMESPACE_BEGIN(math);

class Box;

Naive_NAMESPACE_END(math);

Naive_NAMESPACE_BEGIN(eulerop);

class MakeBodyFaceVertex;
class MakeEdgeKillLoop;
class MakeEdgeVertex;
class MakeFaceEdge;
class MakeGenusBody;
class SplitEdge;
class SpurEdgeVertex;

Naive_NAMESPACE_END(eulerop);

Naive_NAMESPACE_BEGIN(topology);

class Topol : public Naive_Object {
  friend class eulerop::MakeBodyFaceVertex;
  friend class eulerop::MakeEdgeKillLoop;
  friend class eulerop::MakeEdgeVertex;
  friend class eulerop::MakeFaceEdge;
  friend class eulerop::MakeGenusBody;
  friend class eulerop::SplitEdge;
  friend class eulerop::SpurEdgeVertex;

public:
  Topol(const Topol &theOther) Naive_DELETE;

  Naive_EXPORT virtual Topol *Parent() const;

  Naive_EXPORT virtual Topol *TopTopol() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox);

  Naive_DEFINE_RTTI(Topol, Naive_Object);

protected:
  Naive_EXPORT Topol();

  Naive_EXPORT virtual void SetParent(Topol *theParent);
};

Naive_NAMESPACE_END(topology);

using Naive_Topol = ::naivecgl::topology::Topol;
Naive_DEFINE_HANDLE(Naive_Topol);

#endif
