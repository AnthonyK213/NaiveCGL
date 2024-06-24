#pragma once

#include <gtest/gtest.h>
#include <naivecgl/Intersect/Intersection.h>

TEST(NaiveCGLTest_Intersect, Line_Plane_Intersection) {
  Handle_Naive_Line aLine = new Naive_Line();
  Handle_Naive_Plane aPlane = new Naive_Plane();

  Naive_Real aT;
  Naive_Code aCode =
      naivecgl::intersect::Intersection::LinePlane(aLine, aPlane, aT);

  ASSERT_EQ(Naive_Code_invalid_handle, aCode);
}
