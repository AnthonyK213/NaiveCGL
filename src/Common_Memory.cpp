#include <naivecgl/Common/Memory.h>

#include <cstdlib>

Naive_NAMESPACE_BEGIN(common);

MemHandler::MemHandler() {
  Allocator = +[](Naive_Size theNB, void **const thePtr) {
    *thePtr = (void *)malloc(theNB);
    return Naive_Code_ok;
  };
  Deleter = +[](void *thePtr) {
    free(thePtr);
    return Naive_Code_ok;
  };
}

MemHandler::MemHandler(Naive_Code (*theAllocator)(Naive_Size, void **const),
                       Naive_Code (*theDeleter)(void *))
    : Allocator(theAllocator), Deleter(theDeleter) {}

Naive_NAMESPACE_END(common);
