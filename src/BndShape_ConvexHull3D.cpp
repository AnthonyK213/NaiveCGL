#include <naivecgl/BndShape/ConvexHull3D.h>

Naive_NAMESPACE_BEGIN(bndshape);

class QuickHull3D_ {
public:
  QuickHull3D_(const Naive_List<Naive_Point3d> &thePoints)
      : myPoints(thePoints), myConvex(nullptr),
        myStatus(Naive_ConvexHull3D_Failed) {
    if (thePoints.empty()) {
      myStatus = Naive_ConvexHull3D_InsufficientPoint;
      return;
    }

    myStatus = Naive_ConvexHull3D_InitDone;
  }

  void Perform() {
    if (myStatus != Naive_ConvexHull3D_InitDone)
      return;

    myStatus = Naive_ConvexHull3D_Done;
  }

  Naive_ConvexHull3D_Status Status() const { return myStatus; }

  const Naive_H_Mesh ConvexHull() const { return myConvex; }

private:
private:
  const Naive_List<Naive_Point3d> &myPoints;
  Naive_H_Mesh myConvex;
  mutable Naive_ConvexHull3D_Status myStatus;
};

Naive_ConvexHull3D_Status
ConvexHull3D(const Naive_List<Naive_Point3d> &thePoints,
             Naive_H_Mesh &theConvexHull) {
  QuickHull3D_ aHull(thePoints);
  aHull.Perform();

  if (aHull.Status() == Naive_ConvexHull3D_Done)
    theConvexHull = aHull.ConvexHull();

  return aHull.Status();
}

Naive_NAMESPACE_END(bndshape);
