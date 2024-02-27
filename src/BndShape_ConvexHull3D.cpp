#include <naivecgl/BndShape/ConvexHull3D.h>

Naive_NAMESPACE_BEGIN(bndshape);

/* ConvexHull3D::Impl */

ConvexHull3D::Impl::Impl(Naive_Point3d_List &thePoints)
    : myPoints(&thePoints), myStatus(Naive_ConvexHull3D_Failed) {
  if (myPoints->size() < 4) {
    myStatus = Naive_ConvexHull3D_InsufficientPoint;
    return;
  }

  myStatus = Naive_ConvexHull3D_InitDone;
}

ConvexHull3D::Impl::~Impl() {}

Naive_H_Poly ConvexHull3D::Impl::ConvexHull() const {
  if (!myConvexHull || !myConvexHull->IsValid())
    return nullptr;

  return myConvexHull->Soup();
}

/* QuickHull3D */

class QuickHull3D : public ConvexHull3D::Impl {
public:
  QuickHull3D(Naive_Point3d_List &thePoints) : ConvexHull3D::Impl(thePoints) {}

  ~QuickHull3D() {}

public:
  void Perform() override {
    if (myStatus != Naive_ConvexHull3D_InitDone)
      return;

    myStatus = Naive_ConvexHull3D_Done;
  }

  void Add(const Naive_Point3d &thePoint,
           const Naive_Bool thePerform) override {
    if (thePerform)
      Perform();
  }
};

/* Incremental */

/* ConvexHull3D */

ConvexHull3D::ConvexHull3D(const Naive_Point3d_List &thePoints,
                           Naive_ConvexHull3D_Algorithm theAlgo) {
  myPoints = thePoints;
  SetAlgorithm(theAlgo);
}

ConvexHull3D::ConvexHull3D(Naive_Point3d_List &&thePoints,
                           Naive_ConvexHull3D_Algorithm theAlgo) noexcept {
  myPoints = std::move(thePoints);
  SetAlgorithm(theAlgo);
}

ConvexHull3D::~ConvexHull3D() {}

void ConvexHull3D::SetAlgorithm(Naive_ConvexHull3D_Algorithm theAlgo) {
  if (theAlgo == myAlgo && myImpl)
    return;

  myAlgo = theAlgo;

  switch (myAlgo) {
  case Naive_ConvexHull3D_Quickhull: {
    myImpl = std::make_unique<QuickHull3D>(myPoints);
    break;
  }

    // case Naive_ConvexHull3D_Incremental: {
    //   break;
    // }

    // case Naive_ConvexHull3D_DivideAndConquer: {
    //   break;
    // }

  default: {
    myImpl = nullptr;
    return;
  }
  }
}

void ConvexHull3D::Perform() {
  if (!myImpl)
    return;

  myImpl->Perform();
}

void ConvexHull3D::Add(const Naive_Point3d &thePoint,
                       const Naive_Bool thePerform) {
  if (!myImpl)
    return;

  myImpl->Add(thePoint, thePerform);
}

Naive_ConvexHull3D_Status ConvexHull3D::Status() const {
  if (!myImpl)
    return Naive_ConvexHull3D_AlgoNotImplemented;

  return myImpl->Status();
}

Naive_H_Poly ConvexHull3D::ConvexHull() const {
  if (!myImpl)
    return nullptr;

  return myImpl->ConvexHull();
}

Naive_NAMESPACE_END(bndshape);
