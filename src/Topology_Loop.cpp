#include <naivecgl/Topology/Edge.h>
#include <naivecgl/Topology/Face.h>
#include <naivecgl/Topology/Fin.h>
#include <naivecgl/Topology/Loop.h>
#include <naivecgl/Topology/Vertex.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_IMPLEMENT_RTTI(Loop);

Loop::Loop()
    : myFace(nullptr), myFin(nullptr), myType(Naive_Loop_type_outer_c) {}

Naive_Topol *Loop::Parent() const { return myFace; }

Naive_Face *Loop::ParentFace() const { return myFace; }

Naive_Bool Loop::IsTopologicalClosed() const {
  return myFin && myFin->myPrev->GetVertex() == myFin->Twin()->GetVertex();
}

Naive_Code Loop::AppendFin(Naive_Fin *theFin) {
  if (!theFin)
    return Naive_Code_null_arg_address;

  if (IsTopologicalClosed())
    return Naive_Code_err;

  if (myFin) {
    Fin *aFinLast = myFin->myPrev;
    if (aFinLast->GetVertex() == theFin->Twin()->GetVertex() &&
        theFin->GetVertex() == myFin->Twin()->GetVertex()) {
      myFin->myPrev = theFin;
      aFinLast->myNext = theFin;
      theFin->myPrev = aFinLast;
      theFin->myNext = myFin;
      return Naive_Code_ok;
    }
    return Naive_Code_err;
  } else {
    myFin = theFin;
    myFin->myNext = myFin;
    return Naive_Code_ok;
  }
}

Naive_Code Loop::RemoveFin(Naive_Fin *theFin) {
  return Naive_Code_not_implemented;
}

Naive_NAMESPACE_END(topology);
