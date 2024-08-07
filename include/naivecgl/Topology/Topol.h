#ifndef _NaiveCGL_Topology_Topol_HeaderFile
#define _NaiveCGL_Topology_Topol_HeaderFile

#include "../Common/ClassType.h"
#include "Location.h"

Naive_NAMESPACE_BEGIN(topology);

class Topol : public Naive_Object {
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

  Naive_DEFINE_RTTI(Topol, Naive_Object);

protected:
  Topol()
      : myParent(0), myFlags(0), myLocation(),
        myOrient(Naive_Orientation_forward_c) {}

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
