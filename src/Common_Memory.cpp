#include <naivecgl/Common/Memory.h>

Naive_NAMESPACE_BEGIN(common);

MemHandler::MemHandler() {
  Allocator = +[](Naive_Size theNB, void **const thePtr) {
    *thePtr = new char[theNB];
    return Naive_Code_ok;
  };
  Deleter = +[](void *thePtr) {
    delete[] thePtr;
    return Naive_Code_ok;
  };
}

Naive_NAMESPACE_END(common);
