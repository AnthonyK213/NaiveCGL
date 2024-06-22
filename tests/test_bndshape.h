#pragma once

#include <gtest/gtest.h>
#include <naivecgl/BndShape/ConvexHull2D.h>
#include <naivecgl/BndShape/EnclosingDisc.h>

TEST(NaiveCGLTest_BndShape, ConvexHull2D) {
  Naive_Point2dList points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  ::naivecgl::bndshape::ConvexHull2D aCH2d{points};
  aCH2d.Perform();

  Naive_Code code = aCH2d.Status();
  ASSERT_EQ(Naive_Code_ok, code);

  Naive_IntegerList answer{0, 3, 4, 6, 7, 5, 1};
  ASSERT_EQ(answer, aCH2d.ConvexIndices());
}

TEST(NaiveCGLTest_BndShape, EnclosingDisc) {
  Naive_Point2dList points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  ::naivecgl::bndshape::EnclosingDisc aDisc{};
  aDisc.ReBuild(points);

  Naive_Point2d anOrigin{};
  Naive_Real aR{};

  ASSERT_TRUE(aDisc.Circle(anOrigin, aR));
}
