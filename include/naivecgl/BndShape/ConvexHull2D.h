﻿#ifndef _NaiveCGL_BndShape_ConvexHull2D_HeaderFile
#define _NaiveCGL_BndShape_ConvexHull2D_HeaderFile

#include "../Common/Handle.h"
#include "../Math/Pnt2d.h"
#include "../Math/Vec2d.h"

Naive_NAMESPACE_BEGIN(bndshape);

/// @brief Calculates the convex hull of a set of 2d points.
class ConvexHull2D final : public Naive_Object {
public:
  Naive_EXPORT explicit ConvexHull2D(
      const Naive_Pnt2dList1 &thePoints,
      Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull);

  Naive_EXPORT explicit ConvexHull2D(
      Naive_Pnt2dList1 &&thePoints,
      Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull) noexcept;

  Naive_EXPORT ConvexHull2D(const ConvexHull2D &theOther) = delete;

  Naive_EXPORT ConvexHull2D(ConvexHull2D &&theOther) = delete;

  Naive_EXPORT void SetAlgorithm(Naive_Algorithm theAlgo);

  Naive_EXPORT void Perform();

  Naive_EXPORT void Add(const Naive_Pnt2d &thePoint,
                        const Naive_Bool thePerform = Naive_False);

  Naive_EXPORT Naive_Code Status() const;

  Naive_EXPORT Naive_Integer NbConvexPoints() const;

  /// @brief The index(0-based) of convex points in the point list.
  /// @return The indices.
  Naive_EXPORT Naive_IntegerList1 ConvexIndices() const;

  Naive_EXPORT Naive_Pnt2dList1 ConvexPoints() const;

public:
  class Impl {
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
    using Ptr = const Naive_Pnt2d *;
    using Ptrs = Naive_List1<Ptr>;

    explicit Impl(Naive_Pnt2dList1 &thePoints);

    void initPtrs();

  protected:
    Naive_Pnt2dList1 *myPoints;
    Ptrs myPtrs;
    Ptrs myHull;
    mutable Naive_Code myStatus;
  };

private:
  Naive_Pnt2dList1 myPoints;
  ::std::unique_ptr<Impl> myImpl;
  Naive_Algorithm myAlgo;
};

Naive_NAMESPACE_END(bndshape);

#endif
