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

Naive_NAMESPACE_END(eulerop);

Naive_NAMESPACE_BEGIN(topology);

class Topol : public Naive_Object {
  friend class eulerop::MakeBodyFaceVertex;
  friend class eulerop::MakeEdgeKillLoop;
  friend class eulerop::MakeEdgeVertex;
  friend class eulerop::MakeFaceEdge;
  friend class eulerop::MakeGenusBody;
  friend class eulerop::SplitEdge;

public:
  Topol(const Topol &theOther) Naive_DELETE;

  Naive_EXPORT Naive_Handle<Topol> Parent() const { return myParent; }

  Naive_EXPORT const Naive_Location &LocationLocal() const {
    return myLocation;
  }

  Naive_EXPORT void SetLocationLocal(const Naive_Location theLoc) {
    myLocation = theLoc;
  }

  Naive_EXPORT Naive_Orientation OrientationLocal() const { return myOrient; }

  Naive_EXPORT void SetOrientationLocal(const Naive_Orientation theOrient) {
    myOrient = theOrient;
  }

  Naive_EXPORT virtual Naive_Location Location() const;

  Naive_EXPORT virtual Naive_Orientation Orientation() const;

  Naive_EXPORT virtual Naive_Handle<Topol> TopTopol() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox);

  Naive_DEFINE_RTTI(Topol, Naive_Object);

protected:
  Naive_EXPORT Topol();

  void SetParent(const Naive_Handle<Topol> &theParent) {
    myParent = theParent.get();
  }

protected:
  Naive_Location myLocation;
  Topol *myParent;
  Naive_Orientation myOrient;
  Naive_Integer myFlags;
};

Naive_NAMESPACE_END(topology);

using Naive_Topol = ::naivecgl::topology::Topol;
Naive_DEFINE_HANDLE(Naive_Topol);

#endif
