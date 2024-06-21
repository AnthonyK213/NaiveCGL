#ifndef _NaiveCGL_Topology_Topol_HeaderFile
#define _NaiveCGL_Topology_Topol_HeaderFile

#include "../Common/Handle.h"
#include "../Math/Constant.h"
#include "Location.h"

Naive_NAMESPACE_BEGIN(topology);

class Topol : public Naive_Transient {
public:
  Naive_EXPORT Topol *Parent() const { return myParent; }

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

  Naive_EXPORT virtual Naive_Class Class() const = 0;

protected:
  Topol()
      : myParent(0), myTol(math::Constant::DefaultDistanceTolerance()),
        myLocation(), myOrient(Naive_Orientation_forward) {}

protected:
  Topol *myParent;
  Naive_Real myTol;
  Naive_Location myLocation;
  Naive_Orientation myOrient;
};

Naive_NAMESPACE_END(topology);

using Naive_Topol = ::naivecgl::topology::Topol;
Naive_DEFINE_HANDLE(Naive_Topol);

#endif
