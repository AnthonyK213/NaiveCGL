#include <naivecgl/Geom2dAPI/ConvexHull.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(geom2dapi);

/* ConvexHull::Impl */

class ConvexHull::Impl {
public:
  virtual ~Impl();

  virtual void Perform() = 0;

  virtual void Add(const Naive_Pnt2d &thePoint,
                   const Naive_Bool thePerform) = 0;

  Naive_Code Status() const { return myStatus; }

  virtual Naive_Integer NbConvexPoints() const;

  virtual Naive_IntegerList1 ConvexIndices() const;

  virtual Naive_Pnt2dList1 ConvexPoints() const;

protected:
  using PPnt = const Naive_Pnt2d *;
  using PPnts = Naive_List1<PPnt>;

  explicit Impl(Naive_Pnt2dList1 &thePoints);

  void initPtrs();

protected:
  Naive_Pnt2dList1 *myPoints;
  PPnts myPtrs;
  PPnts myHull;
  mutable Naive_Code myStatus;
};

ConvexHull::Impl::Impl(Naive_Pnt2dList1 &thePoints)
    : myPoints(&thePoints), myPtrs{}, myHull{}, myStatus(Naive_Code_err) {
  if (myPoints->size() < 3) {
    myStatus = Naive_Code_insufficient_points;
    return;
  }

  myPtrs.reserve(myPoints->size());
  myHull.reserve(myPoints->size());

  initPtrs();

  myStatus = Naive_Code_initialized;
}

ConvexHull::Impl::~Impl() {}

Naive_Integer ConvexHull::Impl::NbConvexPoints() const {
  return static_cast<Naive_Integer>(myHull.size());
}

Naive_IntegerList1 ConvexHull::Impl::ConvexIndices() const {
  Naive_IntegerList1 result{};

  if (myHull.empty())
    return result;

  result.reserve(myHull.size());

  PPnt first = myPtrs[0];

  for (const PPnt &p : myHull) {
    result.push_back(::std::distance(first, p));
  }

  return result;
}

Naive_Pnt2dList1 ConvexHull::Impl::ConvexPoints() const {
  Naive_Pnt2dList1 result{};

  if (myHull.empty())
    return result;

  result.reserve(myHull.size());

  for (const PPnt &p : myHull) {
    result.push_back(*p);
  }

  return result;
}

void ConvexHull::Impl::initPtrs() {
  myPtrs.clear();

  for (const Naive_Pnt2d &aPoint : *myPoints) {
    myPtrs.push_back(&aPoint);
  }
}

/* QuickHull2D */

class QuickHull2D : public ConvexHull::Impl {
public:
  QuickHull2D(Naive_Pnt2dList1 &thePoints) : ConvexHull::Impl(thePoints) {}

  ~QuickHull2D() {}

public:
  void Perform() Naive_OVERRIDE {
    if (myStatus != Naive_Code_initialized)
      return;

    /* TODO: Check collinear. */

    myStatus = Naive_Code_ok;

    /* Triangle... */
    if (myPtrs.size() == 3) {
      myHull = myPtrs;
      return;
    }

    PPnt a, b, fA, fB;
    extremeX(a, b);

    if (myStatus != Naive_Code_ok)
      return;

    PPnts A = rightOf(myPtrs, a, b, fA); /* Right side of line ab. */
    PPnts B = rightOf(myPtrs, b, a, fB); /* Right side of line ba. */

    myHull.push_back(a);
    half(A, a, b, fA, myHull);
    myHull.push_back(b);
    half(B, b, a, fB, myHull);
  }

  void Add(const Naive_Pnt2d &thePoint,
           const Naive_Bool thePerform) Naive_OVERRIDE {
    Naive_Bool aRealloc = myPoints->capacity() == myPoints->size();
    myPoints->push_back(thePoint);

    if (aRealloc)
      initPtrs();

    /* TODO: If |thePoint| is inside the current hull, update |myHull| if
       |aRealloc|, then set |myStatus| to |Naive_Code_ok|. */

    myHull.clear();
    myStatus = Naive_Code_initialized;

    if (thePerform)
      Perform();
  }

private:
  /**
   * @brief Find points (|a|, |b|) with min and max the value of x.
   *
   * @param a Min
   * @param b Max
   */
  void extremeX(PPnt &a, PPnt &b) const {
    Naive_Real xMin = math::Constant::Infinite();
    Naive_Real xMax = -xMin;

    for (const PPnt &p : myPtrs) {
      if (p->X() < xMin) {
        xMin = p->X();
        a = p;
      }

      if (p->X() > xMax) {
        xMax = p->X();
        b = p;
      }
    }

    /* TODO: Handle this! */
    if (a == b) {
      myStatus = Naive_Code_err;
    }
  }

  /**
   * @brief Find all points which is on the right side of the line ab.
   *
   * @param points The set of points to be searched.
   * @param a The "from point" of the line.
   * @param b The "to point" of the line.
   * @param f The farthest ponit on the right side of the line ab.
   * @return The right-side point set.
   */
  PPnts rightOf(const PPnts &points, PPnt a, PPnt b, PPnt &f) const {
    Naive_Real dist = 0.0;
    PPnts result{};

    for (const PPnt &p : points) {
      if (p == a || p == b)
        continue;

      /* Check if point |p| is on the right side. */

      Naive_XY v = p->XY() - a->XY();
      Naive_XY l = b->XY() - a->XY();

      if (v.x() * l.y() - v.y() * l.x() < 0)
        continue;

      result.push_back(p);

      /* Calculates the distance |d| from point |p| to line ab. */

      l.normalize();
      Naive_XY n = v - l * v.dot(l);
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

  /**
   * @brief Find convex points on a half plane.
   *
   * @param points The point set.
   * @param a
   * @param b
   * @param f
   * @param buf The convex ponits.
   */
  void half(const PPnts &points, PPnt a, PPnt b, PPnt f, PPnts &buf) {
    if (points.empty())
      return;

    PPnt fA, fB;
    PPnts A = rightOf(points, a, f, fA);
    PPnts B = rightOf(points, f, b, fB);

    half(A, a, f, fA, buf);
    buf.push_back(f);
    half(B, f, b, fB, buf);
  }
};

/* Incremental */

/* ConvexHull */

ConvexHull::ConvexHull(const Naive_Pnt2dList1 &thePoints,
                       Naive_Algorithm theAlgo) {
  myPoints = thePoints;
  SetAlgorithm(theAlgo);
}

ConvexHull::ConvexHull(Naive_Pnt2dList1 &&thePoints,
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
    myImpl = ::std::make_unique<QuickHull2D>(myPoints);
    break;
  }

  case Naive_Algorithm_incremental_c: {
    myImpl = nullptr;
    break;
  }

  case Naive_Algorithm_graham_scan_c: {
    myImpl = nullptr;
    break;
  }

  default: {
    myImpl = nullptr;
    return;
  }
  }
}

void ConvexHull::Perform() {
  if (!myImpl)
    return;

  myImpl->Perform();
}

void ConvexHull::Add(const Naive_Pnt2d &thePoint, const Naive_Bool thePerform) {
  if (!myImpl)
    return;

  myImpl->Add(thePoint, thePerform);
}

Naive_Code ConvexHull::Status() const {
  if (!myImpl)
    return Naive_Code_not_implemented;

  return myImpl->Status();
}

Naive_Integer ConvexHull::NbConvexPoints() const {
  if (!myImpl)
    return 0;

  return myImpl->NbConvexPoints();
}

Naive_IntegerList1 ConvexHull::ConvexIndices() const {
  if (!myImpl)
    return {};

  return myImpl->ConvexIndices();
}

Naive_Pnt2dList1 ConvexHull::ConvexPoints() const {
  if (!myImpl)
    return {};

  return myImpl->ConvexPoints();
}

Naive_NAMESPACE_END(geom2dapi);
