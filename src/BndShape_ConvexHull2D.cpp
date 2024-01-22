#include <naivecgl/BndShape/ConvexHull2D.h>

Naive_NAMESPACE_BEGIN(bndshape);

/* ConvexHull2D::Impl */

ConvexHull2D::Impl::Impl(Naive_Point2d_List &thePoints)
    : myPoints(&thePoints), myPtrs{}, myHull{},
      myStatus(Naive_ConvexHull2D_Failed) {
  if (myPoints->size() < 3) {
    myStatus = Naive_ConvexHull2D_InsufficientPoint;
    return;
  }

  myPtrs.reserve(myPoints->size());
  myHull.reserve(myPoints->size());

  initPtrs();

  myStatus = Naive_ConvexHull2D_InitDone;
}

ConvexHull2D::Impl::~Impl() {}

Naive_Integer ConvexHull2D::Impl::NbConvexPoints() const {
  return static_cast<Naive_Integer>(myHull.size());
}

Naive_Integer_List ConvexHull2D::Impl::ConvexIndices() const {
  Naive_Integer_List result{};

  if (myHull.empty())
    return result;

  result.reserve(myHull.size());

  Ptr first = myPtrs[0];

  for (const Ptr &p : myHull) {
    result.push_back(std::distance(first, p));
  }

  return result;
}

Naive_Point2d_List ConvexHull2D::Impl::ConvexPoints() const {
  Naive_Point2d_List result{};

  if (myHull.empty())
    return result;

  result.reserve(myHull.size());

  for (const Ptr &p : myHull) {
    result.push_back(*p);
  }

  return result;
}

void ConvexHull2D::Impl::initPtrs() {
  myPtrs.clear();

  for (const Naive_Point2d &aPoint : *myPoints) {
    myPtrs.push_back(&aPoint);
  }
}

/* QuickHull2D */

class QuickHull2D : public ConvexHull2D::Impl {
public:
  QuickHull2D(Naive_Point2d_List &thePoints) : ConvexHull2D::Impl(thePoints) {}

  ~QuickHull2D() {}

public:
  void Perform() override {
    if (myStatus != Naive_ConvexHull2D_InitDone)
      return;

    // TODO: Check collinear.

    myStatus = Naive_ConvexHull2D_Done;

    /* Triangle... */
    if (myPtrs.size() == 3) {
      myHull = myPtrs;
      return;
    }

    Ptr a, b, fA, fB;
    extremX(a, b);

    if (myStatus != Naive_ConvexHull2D_Done)
      return;

    Ptrs A = rightOf(myPtrs, a, b, fA); /* Right side of line ab. */
    Ptrs B = rightOf(myPtrs, b, a, fB); /* Right side of line ba. */

    myHull.push_back(a);
    half(A, a, b, fA, myHull);
    myHull.push_back(b);
    half(B, b, a, fB, myHull);
  }

  void Add(const Naive_Point2d &thePoint,
           const Naive_Bool thePerform) override {
    bool aRealloc = myPoints->capacity() == myPoints->size();
    myPoints->push_back(thePoint);

    if (aRealloc)
      initPtrs();

    // TODO: If |thePoint| is inside the current hull, update |myHull| if
    // |aRealloc|, then set |myStatus| to |Naive_ConvexHull2D_Done|.

    myHull.clear();
    myStatus = Naive_ConvexHull2D_InitDone;

    if (thePerform)
      Perform();
  }

private:
  /// @brief Find points (|a|, |b|) with min and max the value of x.
  /// @param a Min
  /// @param b Max
  void extremX(Ptr &a, Ptr &b) const {
    Naive_Real xMin = std::numeric_limits<Naive_Real>::infinity();
    Naive_Real xMax = -xMin;

    for (const Ptr &p : myPtrs) {
      if (p->x() < xMin) {
        xMin = p->x();
        a = p;
      }

      if (p->x() > xMax) {
        xMax = p->x();
        b = p;
      }
    }

    /// TODO: Handle this!
    if (a == b) {
      myStatus = Naive_ConvexHull2D_Failed;
    }
  }

  /// @brief Find all points which is on the right side of the line ab.
  /// @param points The set of points to be searched.
  /// @param a The "from point" of the line.
  /// @param b The "to point" of the line.
  /// @param f The farthest ponit on the right side of the line ab.
  /// @return The right-side point set.
  Ptrs rightOf(const Ptrs &points, Ptr a, Ptr b, Ptr &f) const {
    Naive_Real dist = 0.0;
    Ptrs result{};

    for (const Ptr &p : points) {
      if (p == a || p == b)
        continue;

      /* Determines if point |p| is on the right side. */

      Naive_Vector2d v = (*p) - (*a);
      Naive_Vector2d l = (*b) - (*a);

      if (v.x() * l.y() - v.y() * l.x() < 0)
        continue;

      result.push_back(p);

      /* Calculates the distance |d| from point |p| to line ab. */

      l.normalize();
      Naive_Vector2d n = v - l * v.dot(l);
      n.normalize();
      Naive_Real d = n.dot(v);

      /* Finds the farthest point. */

      if (d > dist) {
        dist = d;
        f = p;
      }
    }

    return result;
  }

  /// @brief Find convex points on a half plane.
  /// @param points The point set.
  /// @param a
  /// @param b
  /// @param f
  /// @param buf The convex ponits.
  void half(const Ptrs &points, Ptr a, Ptr b, Ptr f, Ptrs &buf) {
    if (points.empty())
      return;

    Ptr fA, fB;
    Ptrs A = rightOf(points, a, f, fA);
    Ptrs B = rightOf(points, f, b, fB);

    half(A, a, f, fA, buf);
    buf.push_back(f);
    half(B, f, b, fB, buf);
  }
};

/* Incremental */

/* ConvexHull2D */

ConvexHull2D::ConvexHull2D(const Naive_Point2d_List &thePoints,
                           Naive_ConvexHull2D_Algorithm theAlgo) {
  myPoints = thePoints;
  SetAlgorithm(theAlgo);
}

ConvexHull2D::ConvexHull2D(Naive_Point2d_List &&thePoints,
                           Naive_ConvexHull2D_Algorithm theAlgo) noexcept {
  myPoints = std::move(thePoints);
  SetAlgorithm(theAlgo);
}

ConvexHull2D::~ConvexHull2D() {}

void ConvexHull2D::SetAlgorithm(Naive_ConvexHull2D_Algorithm theAlgo) {
  if (theAlgo == myAlgo && myImpl)
    return;

  myAlgo = theAlgo;

  switch (myAlgo) {
  case Naive_ConvexHull2D_Quickhull: {
    myImpl = std::make_unique<QuickHull2D>(myPoints);
    break;
  }

    // case Naive_ConvexHull2D_Incremental: {
    //   break;
    // }

    // case Naive_ConvexHull2D_GrahamScan: {
    //   break;
    // }

  default: {
    myImpl = nullptr;
    return;
  }
  }
}

void ConvexHull2D::Perform() {
  if (!myImpl)
    return;

  myImpl->Perform();
}

void ConvexHull2D::Add(const Naive_Point2d &thePoint,
                       const Naive_Bool thePerform) {
  if (!myImpl)
    return;

  myImpl->Add(thePoint, thePerform);
}

Naive_ConvexHull2D_Status ConvexHull2D::Status() const {
  if (!myImpl)
    return Naive_ConvexHull2D_AlgoNotImplemented;

  return myImpl->Status();
}

Naive_Integer ConvexHull2D::NbConvexPoints() const {
  if (!myImpl)
    return 0;

  return myImpl->NbConvexPoints();
}

Naive_Integer_List ConvexHull2D::ConvexIndices() const {
  if (!myImpl)
    return {};

  return myImpl->ConvexIndices();
}

Naive_Point2d_List ConvexHull2D::ConvexPoints() const {
  if (!myImpl)
    return {};

  return myImpl->ConvexPoints();
}

Naive_NAMESPACE_END(bndshape);
