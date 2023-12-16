#include <naivecgl/BndShape/ConvexHull.h>

Naive_Namespace_Begin(bndshape);

class _QuickHull2D_ {
  using Ptr = const Naive_Point2d *;
  using Ptrs = Naive_List<Ptr>;

public:
  _QuickHull2D_(const Naive_List<Naive_Point2d> &points)
      : m_status(Naive_Fail) {
    if (points.empty())
      return;

    m_points.reserve(points.size());
    m_hull.reserve(points.size());

    for (const Naive_Point2d &point : points) {
      m_points.push_back(&point);
    }

    m_status = Naive_Ok;
  }

  ~_QuickHull2D_() {}

public:
  void perform() {
    if (status() != Naive_Ok)
      return;

    Ptr a, b, fA, fB;
    setStatus(extremX(a, b));

    if (status() != Naive_Ok)
      return;

    Ptrs A = rightOf(m_points, a, b, fA);
    Ptrs B = rightOf(m_points, b, a, fB);

    m_hull.push_back(a);
    half(A, a, b, fA, m_hull);
    m_hull.push_back(b);
    half(B, b, a, fB, m_hull);
  }

  Naive_Code status() const { return m_status; }

  Naive_List<Naive_Integer> convexIndices() const {
    Naive_List<Naive_Integer> result{};

    if (m_hull.empty())
      return result;

    result.reserve(m_hull.size());

    Ptr first = m_points[0];

    for (const Ptr &p : m_hull) {
      result.push_back(std::distance(first, p));
    }

    return result;
  }

private:
  Naive_Code extremX(Ptr &a, Ptr &b) const {
    Naive_Real xMin = std::numeric_limits<Naive_Real>::infinity();
    Naive_Real xMax = -xMin;

    for (const Ptr &p : m_points) {
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

  void setStatus(Naive_Code theStatus) { m_status = theStatus; }

private:
  Ptrs m_points{};
  Ptrs m_hull{};
  Naive_Code m_status;
};

Naive_Code convexHull2D(const Naive_List<Naive_Point2d> &points,
                        Naive_List<Naive_Integer> &convexIndices) {
  _QuickHull2D_ hull{points};
  hull.perform();

  if (hull.status() == Naive_Ok)
    convexIndices = hull.convexIndices();

  return hull.status();
}

Naive_H_Mesh convexHull3D(const Naive_List<Naive_Point3d> &points) {
  throw std::runtime_error("Not implemented yet");
}

Naive_Namespace_End(bndshape);
