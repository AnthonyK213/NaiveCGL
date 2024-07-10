#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Geom2dAPI/ConvexHull.h>
#include <naivecgl/Geom2dAPI/EnclosingDisc.h>

TEST(NaiveCGLTest_Geom2dAPI, ConvexHull) {
  Naive_Pnt2dList1 points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  ::naivecgl::geom2dapi::ConvexHull aCH2d{::std::move(points)};
  aCH2d.Perform();

  Naive_Code code = aCH2d.Status();
  ASSERT_EQ(Naive_Code_ok, code);

  Naive_IntegerList1 answer{0, 3, 4, 6, 7, 5, 1};
  ASSERT_EQ(answer, aCH2d.ConvexIndices());
}

TEST(NaiveCGLTest_Geom2dAPI, EnclosingDisc) {
  Naive_Pnt2dList1 points{
      {0, 2}, {1, 3}, {2, 2}, {2, 0}, {3, 1}, {3, 4}, {4, 2}, {4, 3},
  };

  ::naivecgl::geom2dapi::EnclosingDisc aDisc{};
  aDisc.ReBuild(points);

  Naive_Pnt2d anOrigin{};
  Naive_Real aR{};

  ASSERT_TRUE(aDisc.Result(anOrigin, aR));
}
