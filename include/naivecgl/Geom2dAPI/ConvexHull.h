#ifndef _NaiveCGL_Geom2dAPI_ConvexHull_HeaderFile
#define _NaiveCGL_Geom2dAPI_ConvexHull_HeaderFile

#include "../Math/Pnt2d.h"
#include "../Math/Vec2d.h"

#include <memory>

Naive_NAMESPACE_BEGIN(geom2dapi);

/**
 * @brief Calculates the convex hull of a set of 2d points.
 *
 */
class ConvexHull final {
public:
  Naive_EXPORT explicit ConvexHull(
      const Naive_Pnt2dList1 &thePoints,
      Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull_c);

  Naive_EXPORT explicit ConvexHull(
      Naive_Pnt2dList1 &&thePoints,
      Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull_c) noexcept;

  Naive_EXPORT ConvexHull(const ConvexHull &theOther) Naive_DELETE;

  Naive_EXPORT ConvexHull(ConvexHull &&theOther) Naive_DELETE;

  Naive_EXPORT ~ConvexHull();

  Naive_EXPORT void SetAlgorithm(Naive_Algorithm theAlgo);

  Naive_EXPORT void Perform();

  Naive_EXPORT void Add(const Naive_Pnt2d &thePoint,
                        const Naive_Bool thePerform = Naive_False);

  Naive_EXPORT Naive_Code Status() const;

  Naive_EXPORT Naive_Integer NbConvexPoints() const;

  /**
   * @brief The index(0-based) of convex points in the point list.
   *
   * @return The indices.
   */
  Naive_EXPORT Naive_IntegerList1 ConvexIndices() const;

  Naive_EXPORT Naive_Pnt2dList1 ConvexPoints() const;

public:
  class Impl;

private:
  Naive_Pnt2dList1 myPoints;
  ::std::unique_ptr<Impl> myImpl;
  Naive_Algorithm myAlgo;
};

Naive_NAMESPACE_END(geom2dapi);

#endif
