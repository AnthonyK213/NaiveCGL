﻿#ifndef _NaiveCGL_BndShape_ConvexHull2D_HeaderFile
#define _NaiveCGL_BndShape_ConvexHull2D_HeaderFile

#include <naivecgl/Geometry/Point2d.h>
#include <naivecgl/Geometry/Vector2d.h>

Naive_NAMESPACE_BEGIN(bndshape);

/// @brief Calculates the convex hull of a set of 2d points.
class ConvexHull2D {
public:
  Naive_EXPORT explicit ConvexHull2D(
      const Naive_Point2dList &thePoints,
      Naive_ConvexHull2D_Algorithm theAlgo = Naive_ConvexHull2D_Quickhull);

  Naive_EXPORT explicit ConvexHull2D(Naive_Point2dList &&thePoints,
                                     Naive_ConvexHull2D_Algorithm theAlgo =
                                         Naive_ConvexHull2D_Quickhull) noexcept;

  Naive_EXPORT ConvexHull2D(const ConvexHull2D &theOther) = delete;

  Naive_EXPORT ConvexHull2D(ConvexHull2D &&theOther) = delete;

  Naive_EXPORT ~ConvexHull2D();

  Naive_EXPORT void SetAlgorithm(Naive_ConvexHull2D_Algorithm theAlgo);

  Naive_EXPORT void Perform();

  Naive_EXPORT void Add(const Naive_Point2d &thePoint,
                        const Naive_Bool thePerform = false);

  Naive_EXPORT Naive_ConvexHull2D_Status Status() const;

  Naive_EXPORT Naive_Integer NbConvexPoints() const;

  /// @brief The index(0-based) of convex points in the point list.
  /// @return The indices.
  Naive_EXPORT Naive_IntegerList ConvexIndices() const;

  Naive_EXPORT Naive_Point2dList ConvexPoints() const;

public:
  class Impl {
  public:
    virtual ~Impl();

    virtual void Perform() = 0;

    virtual void Add(const Naive_Point2d &thePoint,
                     const Naive_Bool thePerform) = 0;

    Naive_ConvexHull2D_Status Status() const { return myStatus; }

    virtual Naive_Integer NbConvexPoints() const;

    virtual Naive_IntegerList ConvexIndices() const;

    virtual Naive_Point2dList ConvexPoints() const;

  protected:
    using Ptr = const Naive_Point2d *;
    using Ptrs = Naive_List<Ptr>;

    explicit Impl(Naive_Point2dList &thePoints);

    void initPtrs();

  protected:
    Naive_Point2dList *myPoints;
    Ptrs myPtrs;
    Ptrs myHull;
    mutable Naive_ConvexHull2D_Status myStatus;
  };

private:
  Naive_Point2dList myPoints;
  std::unique_ptr<Impl> myImpl;
  Naive_ConvexHull2D_Algorithm myAlgo;
};

Naive_NAMESPACE_END(bndshape);

#endif
