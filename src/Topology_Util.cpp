#include <naivecgl/Topology/Util.h>

Naive_NAMESPACE_BEGIN(topology);

Naive_Orientation Util::Compose(const Naive_Orientation theO1,
                                const Naive_Orientation theO2) {
  static const Naive_Orientation Naive_Orientation_ComposeTable[4][4] = {
      {Naive_Orientation_forward_c, Naive_Orientation_reversed_c,
       Naive_Orientation_internal_c, Naive_Orientation_external_c},
      {Naive_Orientation_reversed_c, Naive_Orientation_forward_c,
       Naive_Orientation_internal_c, Naive_Orientation_external_c},
      {Naive_Orientation_internal_c, Naive_Orientation_internal_c,
       Naive_Orientation_internal_c, Naive_Orientation_internal_c},
      {Naive_Orientation_external_c, Naive_Orientation_external_c,
       Naive_Orientation_external_c, Naive_Orientation_external_c},
  };
  return Naive_Orientation_ComposeTable[(Naive_Integer)theO2]
                                       [(Naive_Integer)theO1];
}

Naive_Orientation Util::Reverse(const Naive_Orientation theOri) {
  static const Naive_Orientation Naive_Orientation_ReverseTable[4] = {
      Naive_Orientation_reversed_c,
      Naive_Orientation_forward_c,
      Naive_Orientation_internal_c,
      Naive_Orientation_external_c,
  };
  return Naive_Orientation_ReverseTable[(Naive_Integer)theOri];
}

Naive_NAMESPACE_END(topology);
