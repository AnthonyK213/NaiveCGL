#ifndef _NaiveCGL_Topology_Region_HeaderFile
#define _NaiveCGL_Topology_Region_HeaderFile

#include "../Collection/LinkedList.h"
#include "Topol.h"

Naive_NAMESPACE_BEGIN(topology);

class Body;
class Shell;

class Region final : public Naive_Topol {
  friend class euler_op::MakeBodyFaceVertex;

public:
  Naive_EXPORT Region();

  Naive_EXPORT virtual Topol *Parent() const Naive_OVERRIDE;

  Naive_EXPORT Body *ParentBody() const;

  Naive_EXPORT virtual void GetBox(math::Box &theBox) Naive_OVERRIDE;

  Naive_DEFINE_RTTI(Region, Naive_Topol);

protected:
  Naive_EXPORT virtual void SetParent(Naive_Topol *theParent) Naive_OVERRIDE;

private:
  Naive_LinkedList<Naive_Handle<Shell>> myShells;
  Body *myBody;                /* Parent body. */
  Region *myPrev;              /* Previous region in myBody. */
  Naive_Handle<Region> myNext; /* Next region in myBody. */
};

Naive_NAMESPACE_END(topology);

using Naive_Region = ::naivecgl::topology::Region;
Naive_DEFINE_HANDLE(Naive_Region);

#endif
