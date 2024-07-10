#ifndef _NaiveCGL_GeomAPI_ConvexHull_HeaderFile
#define _NaiveCGL_GeomAPI_ConvexHull_HeaderFile

#include "../Geometry/Mesh.h"
#include "../Geometry/Triangulation.h"
#include "../Math/Pnt3d.h"

Naive_NAMESPACE_BEGIN(geomapi);

/// @brief Calculates the convex hull of a set of 3d points.
class ConvexHull final {
public:
  Naive_EXPORT
  ConvexHull(const Naive_Pnt3dList1 &thePoints,
             Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull_c);

  Naive_EXPORT
  ConvexHull(Naive_Pnt3dList1 &&thePoints,
             Naive_Algorithm theAlgo = Naive_Algorithm_quick_hull_c) noexcept;

  Naive_EXPORT ConvexHull(const ConvexHull &theOther) Naive_DELETE;

  Naive_EXPORT ConvexHull(ConvexHull &&theOther) Naive_DELETE;

  Naive_EXPORT void SetAlgorithm(Naive_Algorithm theAlgo);

  Naive_EXPORT void Perform();

  Naive_EXPORT void Add(const Naive_Pnt3d &thePoint,
                        const Naive_Bool thePerform = Naive_False);

  Naive_EXPORT Naive_Code Status() const;

  Naive_EXPORT Handle_Naive_Poly Result() const;

public:
  class Impl {
  public:
    virtual ~Impl();

    virtual void Perform() = 0;

    virtual void Add(const Naive_Pnt3d &thePoint,
                     const Naive_Bool thePerform) = 0;

    Naive_Code Status() const { return myStatus; }

    virtual Handle_Naive_Poly Result() const;

  protected:
    explicit Impl(Naive_Pnt3dList1 &thePoints);

  protected:
    Naive_Pnt3dList1 *myPoints;
    Handle_Naive_Mesh myConvexHull;
    mutable Naive_Code myStatus;
  };

private:
  Naive_Pnt3dList1 myPoints;
  ::std::unique_ptr<Impl> myImpl;
  Naive_Algorithm myAlgo;
};

Naive_NAMESPACE_END(geomapi);

#endif
