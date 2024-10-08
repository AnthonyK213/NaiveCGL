﻿#ifndef _NaiveCGL_Math_Box_HeaderFile
#define _NaiveCGL_Math_Box_HeaderFile

#include "Pnt3d.h"

Naive_NAMESPACE_BEGIN(math);

class Trsf3d;
class Vec3d;

class Box final {
public:
  Naive_EXPORT Box();

  Naive_EXPORT Box(const Naive_Pnt3d &theA, const Naive_Pnt3d &theB);

  Naive_EXPORT static const Box &Unset();

  Naive_EXPORT static const Box &Void();

  Naive_EXPORT Naive_Bool IsValid() const;

  Naive_EXPORT Naive_Bool IsVoid() const;

  Naive_EXPORT Naive_Bool IsPoint() const;

  Naive_EXPORT const Naive_Pnt3d &Min() const { return myMin; }

  Naive_EXPORT const Naive_Pnt3d &Max() const { return myMax; }

  Naive_EXPORT Vec3d Diagonal() const;

  Naive_EXPORT Naive_Pnt3d Center() const { return 0.5 * (myMax + myMin); }

  Naive_EXPORT Naive_Pnt3d Corner(Naive_Bool theMinX, Naive_Bool theMinY,
                                  Naive_Bool theMinZ) const;
  
  /**
   * @brief Get corners of the box.
   * 
   * @return Coners with order:
   * [0] = {Min.X, Min.Y, Min.Z};
   * [1] = {Max.X, Min.Y, Min.Z};
   * [2] = {Max.X, Max.Y, Min.Z};
   * [3] = {Min.X, Max.Y, Min.Z};
   * [4] = {Min.X, Min.Y, Max.Z};
   * [5] = {Max.X, Min.Y, Max.Z};
   * [6] = {Max.X, Max.Y, Max.Z};
   * [7] = {Min.X, Max.Y, Max.Z}.
   */
  Naive_EXPORT Naive_Pnt3dList1 Corners() const;

  Naive_EXPORT Naive_Bool Contains(const Box &theBox) const;

  Naive_EXPORT Naive_Bool Contains(const Box &theBox,
                                   const Naive_Bool theStrict) const;

  Naive_EXPORT Naive_Bool Contains(const Naive_Pnt3d &thePoint) const;

  Naive_EXPORT Naive_Bool Contains(const Naive_Pnt3d &thePoint,
                                   const Naive_Bool theStrict) const;

  Naive_EXPORT void Update(const Naive_Real theXMin, const Naive_Real theYMin,
                           const Naive_Real theZMin, const Naive_Real theXMax,
                           const Naive_Real theYMax, const Naive_Real theZMax);

  Naive_EXPORT void Update(const Naive_Real theX, const Naive_Real theY,
                           const Naive_Real theZ);

  Naive_EXPORT void Add(const Box &theOther);

  Naive_EXPORT void Add(const Naive_Pnt3d &thePoint);

  Naive_EXPORT Naive_Pnt3d PointAt(const Naive_Real theTx,
                                   const Naive_Real theTy,
                                   const Naive_Real theTz) const;

  Naive_EXPORT Naive_Bool Transform(const Trsf3d &theTrsf);

  Naive_EXPORT Box Transformed(const Trsf3d &theTrsf) const;

  Naive_EXPORT static Box Intersection(const Box theA, const Box theB);

  Naive_EXPORT static Box Union(const Box theA, const Box theB);

  Naive_EXPORT static Box Union(const Box theBox, const Naive_Pnt3d &thePnt);

private:
  Naive_Bool isSet() const;

  Naive_Bool isValid() const;

  Naive_Bool isVoid() const;

  Naive_Bool isPoint() const;

private:
  Naive_Pnt3d myMin;
  Naive_Pnt3d myMax;
};

Naive_NAMESPACE_END(math);

using Naive_Box = ::naivecgl::math::Box;

#endif
