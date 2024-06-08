#include <naivecgl/BndShape/ConvexHull3D.h>

Naive_NAMESPACE_BEGIN(bndshape);

/* ConvexHull3D::Impl */

ConvexHull3D::Impl::Impl(Naive_Point3dList &thePoints)
    : myPoints(&thePoints), myStatus(Naive_Code_err) {
  if (myPoints->size() < 4) {
    myStatus = Naive_Code_insufficient_points;
    return;
  }

  myStatus = Naive_Code_initialized;
}

ConvexHull3D::Impl::~Impl() {}

Handle_Naive_Poly ConvexHull3D::Impl::ConvexHull() const {
  if (!myConvexHull || !myConvexHull->IsValid())
    return nullptr;

  return myConvexHull->Soup();
}

/* QuickHull3D */

class QuickHull3D : public ConvexHull3D::Impl {
public:
  QuickHull3D(Naive_Point3dList &thePoints) : ConvexHull3D::Impl(thePoints) {}

  ~QuickHull3D() {}

public:
  void Perform() override {
    if (myStatus != Naive_Code_initialized)
      return;

    myStatus = Naive_Code_ok;
  }

  void Add(const Naive_Point3d &thePoint,
           const Naive_Bool thePerform) override {
    if (thePerform)
      Perform();
  }
};

/* Incremental */

/* ConvexHull3D */

ConvexHull3D::ConvexHull3D(const Naive_Point3dList &thePoints,
                           Naive_Algorithm theAlgo) {
  myPoints = thePoints;
  SetAlgorithm(theAlgo);
}

ConvexHull3D::ConvexHull3D(Naive_Point3dList &&thePoints,
                           Naive_Algorithm theAlgo) noexcept {
  myPoints = ::std::move(thePoints);
  SetAlgorithm(theAlgo);
}

void ConvexHull3D::SetAlgorithm(Naive_Algorithm theAlgo) {
  if (theAlgo == myAlgo && myImpl)
    return;

  myAlgo = theAlgo;

  switch (myAlgo) {
  case Naive_Algorithm_quick_hull: {
    myImpl = ::std::make_unique<QuickHull3D>(myPoints);
    break;
  }

  case Naive_Algorithm_incremental: {
    myImpl = nullptr;
    break;
  }

  case Naive_Algorithm_divide_and_conquer: {
    myImpl = nullptr;
    break;
  }

  default: {
    myImpl = nullptr;
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

Naive_Code ConvexHull3D::Status() const {
  if (!myImpl)
    return Naive_Code_not_implemented;

  return myImpl->Status();
}

Handle_Naive_Poly ConvexHull3D::ConvexHull() const {
  if (!myImpl)
    return nullptr;

  return myImpl->ConvexHull();
}

Naive_NAMESPACE_END(bndshape);
