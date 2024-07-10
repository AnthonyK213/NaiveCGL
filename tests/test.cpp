#include "test_geom2dapi.h"
#include "test_geometry.h"
#include "test_interface.h"
#include "test_intersect.h"
#include "test_math.h"
#include "test_tessellation.h"
#include "test_topology.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
