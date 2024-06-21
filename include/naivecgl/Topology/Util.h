#ifndef _NaiveCGL_Topology_Util_HeaderFile
#define _NaiveCGL_Topology_Util_HeaderFile

#include "../Common/Macro.h"
#include "../Common/Type.h"

Naive_NAMESPACE_BEGIN(topology);

class Util {
public:
  Naive_EXPORT static Naive_Orientation Compose(const Naive_Orientation theO1,
                                                const Naive_Orientation theO2);

  Naive_EXPORT static Naive_Orientation Reverse(const Naive_Orientation theOri);
};

Naive_NAMESPACE_END(topology);

#endif
