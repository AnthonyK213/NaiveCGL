#ifndef _NaiveCGL_Common_Memory_HeaderFile
#define _NaiveCGL_Common_Memory_HeaderFile

#include "Macro.h"
#include "Type.h"

Naive_NAMESPACE_BEGIN(common);

struct MemHandler {
  Naive_Code (*Allocator)(Naive_Size, void **const);
  Naive_Code (*Deleter)(void *);

  Naive_EXPORT MemHandler();

  Naive_EXPORT MemHandler(Naive_Code (*theAllocator)(Naive_Size, void **const),
                          Naive_Code (*theDeleter)(void *));
};

Naive_NAMESPACE_END(common);

#endif
