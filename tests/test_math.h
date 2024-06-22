#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Math/Polynomial.h>

TEST(NaiveCGLTest_Math, Polynomial) {
  naivecgl::math::Polynomial aP({3, 1, 4, 1, 5, 9});
  ASSERT_EQ(5, aP.Degree());
  ASSERT_DOUBLE_EQ(397, aP.Evaluate(2));
  auto aP_3 = aP.Derivative(3);
  ASSERT_TRUE(aP_3.IsEqual(naivecgl::math::Polynomial({6, 120, 540})));

  naivecgl::math::Polynomial aP1({2, 1});
  auto aP2 = aP.Multiplied(aP1);
  ASSERT_TRUE(aP2.IsEqual(naivecgl::math::Polynomial({6, 5, 9, 6, 11, 23, 9})));
}
