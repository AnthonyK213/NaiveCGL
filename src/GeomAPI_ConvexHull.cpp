#include <naivecgl/GeomAPI/ConvexHull.h>

Naive_NAMESPACE_BEGIN(geom_api);

/* ConvexHull::Impl */

class ConvexHull::Impl {
public:
  virtual ~Impl();

  virtual void Perform() = 0;

  virtual void Add(const Naive_Pnt3d &thePoint,
                   const Naive_Bool thePerform) = 0;

  Naive_Code Status() const { return myStatus; }

  virtual Handle_Naive_Triangulation Result() const;

protected:
  explicit Impl(Naive_Pnt3dList1 &thePoints);

protected:
  Naive_Pnt3dList1 *myPoints;
  Handle_Naive_Mesh myConvexHull;
  mutable Naive_Code myStatus;
};

ConvexHull::Impl::Impl(Naive_Pnt3dList1 &thePoints)
    : myPoints(&thePoints), myStatus(Naive_Code_err) {
  if (myPoints->size() < 4) {
    myStatus = Naive_Code_insufficient_points;
    return;
  }

  myStatus = Naive_Code_initialized;
}

ConvexHull::Impl::~Impl() {}

Handle_Naive_Triangulation ConvexHull::Impl::Result() const {
  if (!myConvexHull || !myConvexHull->IsValid())
    return nullptr;

  return myConvexHull->GetTriangulation();
}

/* QuickHull */

class QuickHull : public ConvexHull::Impl {
public:
  QuickHull(Naive_Pnt3dList1 &thePoints) : ConvexHull::Impl(thePoints) {}

  ~QuickHull() {}

public:
  void Perform() Naive_OVERRIDE {
    if (myStatus != Naive_Code_initialized)
      return;

    myStatus = Naive_Code_ok;
  }

  void Add(const Naive_Pnt3d &thePoint,
           const Naive_Bool thePerform) Naive_OVERRIDE {
    if (thePerform)
      Perform();
  }
};

/* Incremental */

/* ConvexHull */

ConvexHull::ConvexHull(const Naive_Pnt3dList1 &thePoints,
                       Naive_Algorithm theAlgo) {
  myPoints = thePoints;
  SetAlgorithm(theAlgo);
}

ConvexHull::ConvexHull(Naive_Pnt3dList1 &&thePoints,
                       Naive_Algorithm theAlgo) noexcept {
  myPoints = ::std::move(thePoints);
  SetAlgorithm(theAlgo);
}

ConvexHull::~ConvexHull() {}

void ConvexHull::SetAlgorithm(Naive_Algorithm theAlgo) {
  if (theAlgo == myAlgo && myImpl)
    return;

  myAlgo = theAlgo;

  switch (myAlgo) {
  case Naive_Algorithm_quick_hull_c: {
    myImpl = ::std::make_unique<QuickHull>(myPoints);
    break;
  }

  case Naive_Algorithm_incremental_c: {
    myImpl = nullptr;
    break;
  }

  case Naive_Algorithm_divide_and_conquer_c: {
    myImpl = nullptr;
    break;
  }

  default: {
    myImpl = nullptr;
  }
  }
}

void ConvexHull::Perform() {
  if (!myImpl)
    return;

  myImpl->Perform();
}

void ConvexHull::Add(const Naive_Pnt3d &thePoint, const Naive_Bool thePerform) {
  if (!myImpl)
    return;

  myImpl->Add(thePoint, thePerform);
}

Naive_Code ConvexHull::Status() const {
  if (!myImpl)
    return Naive_Code_not_implemented;

  return myImpl->Status();
}

Handle_Naive_Triangulation ConvexHull::Result() const {
  if (!myImpl)
    return nullptr;

  return myImpl->Result();
}

Naive_NAMESPACE_END(geom_api);
