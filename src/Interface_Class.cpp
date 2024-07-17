#include <naivecgl/Common/TClassType.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Class_ask_superclass(Naive_Class_t class_,
                                        Naive_Class_t *const superclass) {
  if (!superclass)
    return Naive_Code_null_arg_address;

  auto t = Naive_TClassType::Resolve(static_cast<Naive_Class>(class_));
  *superclass = t.Super();

  return Naive_Code_ok;
}

Naive_Code_t Naive_Class_is_subclass(Naive_Class_t may_be_subclass,
                                     Naive_Class_t class_,
                                     Naive_Logical_t *const is_subclass) {
  if (!is_subclass)
    return Naive_Code_null_arg_address;

  auto t = Naive_TClassType::Resolve(static_cast<Naive_Class>(may_be_subclass));
  *is_subclass = t.IsSubClass(static_cast<Naive_Class>(class_));

  return Naive_Code_ok;
}
