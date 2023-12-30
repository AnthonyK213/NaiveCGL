#include <naivecgl/BndShape/ConvexHull.h>

Naive_Namespace_Begin(bndshape);

class QuickHull2D_ {
  using Ptr = const Naive_Point2d *;
  using Ptrs = Naive_List<Ptr>;

public:
  QuickHull2D_(const Naive_List<Naive_Point2d> &thePoints) : myStatus(Naive_Fail) {
    if (thePoints.empty())
      return;

    myPoints.reserve(thePoints.size());
    myHull.reserve(thePoints.size());

    for (const Naive_Point2d &aPoint : thePoints) {
      myPoints.push_back(&aPoint);
    }

    myStatus = Naive_Ok;
  }

  ~QuickHull2D_() {}

public:
  void Perform() {
    if (Status() != Naive_Ok)
      return;

    Ptr a, b, fA, fB;
    setStatus(extremX(a, b));

    if (Status() != Naive_Ok)
      return;

    Ptrs A = rightOf(myPoints, a, b, fA);
    Ptrs B = rightOf(myPoints, b, a, fB);

    myHull.push_back(a);
    half(A, a, b, fA, myHull);
    myHull.push_back(b);
    half(B, b, a, fB, myHull);
  }

  Naive_Code Status() const { return myStatus; }

  Naive_List<Naive_Integer> ConvexIndices() const {
    Naive_List<Naive_Integer> result{};

    if (myHull.empty())
      return result;

    result.reserve(myHull.size());

    Ptr first = myPoints[0];

    for (const Ptr &p : myHull) {
      result.push_back(std::distance(first, p));
    }

    return result;
  }

private:
  Naive_Code extremX(Ptr &a, Ptr &b) const {
    Naive_Real xMin = std::numeric_limits<Naive_Real>::infinity();
    Naive_Real xMax = -xMin;

    for (const Ptr &p : myPoints) {
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
      return Naive_Fail;
    }

    return Naive_Ok;
  }

  Ptrs rightOf(const Ptrs &points, Ptr a, Ptr b, Ptr &f) const {
    Naive_Real dist = 0.0;
    Ptrs result{};

    for (const Ptr &p : points) {
      Naive_Vector2d v = (*p) - (*a);
      Naive_Vector2d l = (*b) - (*a);

      if (p == a || p == b)
        continue;

      if (v.x() * l.y() - v.y() * l.x() < 0)
        continue;

      result.push_back(p);

      l.normalize();

      Naive_Vector2d n = v - l * v.dot(l);
      n.normalize();

      Naive_Real d = n.dot(v);

      if (d > dist) {
        dist = d;
        f = p;
      }
    }

    return result;
  }

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

  void setStatus(Naive_Code theStatus) { myStatus = theStatus; }

private:
  Ptrs myPoints{};
  Ptrs myHull{};
  Naive_Code myStatus;
};

Naive_Code ConvexHull2D(const Naive_List<Naive_Point2d> &thePoints,
                        Naive_List<Naive_Integer> &theConvexIndices) {
  QuickHull2D_ aHull{thePoints};
  aHull.Perform();

  if (aHull.Status() == Naive_Ok)
    theConvexIndices = aHull.ConvexIndices();

  return aHull.Status();
}

Naive_H_Mesh ConvexHull3D(const Naive_List<Naive_Point3d> &thePoints) {
  throw std::runtime_error("Not implemented yet");
}

Naive_Namespace_End(bndshape);
