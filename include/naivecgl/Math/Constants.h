#ifndef _NaiveCGL_Math_Constants_HeaderFile
#define _NaiveCGL_Math_Constants_HeaderFile

#include <naivecgl/Common/def.h>

#include <cmath>

Naive_Namespace_Begin(math);

static constexpr Naive_Real PI = 3.14159265358979323846;

static constexpr Naive_Real DefaultAngleTolerance = PI / 180.0;

static constexpr Naive_Real DefaultDistanceToleranceMillimeters = 0.01;

static constexpr Naive_Real Epsilon = 2.2204460492503131e-16;

static constexpr Naive_Real HalfPI = PI / 2.0;

static constexpr Naive_Real QuaterPI = PI / 4.0;

static constexpr Naive_Real SqrtEpsilon = 1.490116119385000000e-8;

static constexpr Naive_Real Tau = PI * 2.0;

static constexpr Naive_Real TwoPI = Tau;

static constexpr Naive_Real UnsetValue = -1.23432101234321e+308;

static constexpr Naive_Real ZeroTolerance = 2.3283064365386962890625e-10;

static constexpr float UnsetSingle = -1.234321e+38f;

static constexpr Naive_Integer UnsetIntIndex = INT_MIN + 1;

Naive_Namespace_End(math);

#endif
