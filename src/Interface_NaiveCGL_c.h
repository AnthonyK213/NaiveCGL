#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1
#define _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1

#include <naivecgl/Interface/NaiveCGL_c.h>

#include <cstdlib>

#define Naive_ROSTER_ASK(T, Tag_, Var_)                                        \
  Naive_Handle<T> Var_;                                                        \
  do {                                                                         \
    Naive_TObject __naive_tobj__;                                              \
    Naive_Code __naive_code__ =                                                \
        Naive_Roster::Resolve().Find(Tag_, __naive_tobj__);                    \
    if (__naive_code__ != Naive_Code_ok) {                                     \
      return __naive_code__;                                                   \
    }                                                                          \
    Var_ = Naive_Handle<T>::DownCast(__naive_tobj__.GetObject());              \
    if (!Var_) {                                                               \
      return Naive_Code_invalid_object;                                        \
    }                                                                          \
  } while (0)

#define Naive_ROSTER_ADD(Obj_, Tag_)                                           \
  do {                                                                         \
    Naive_TObject __naive_tobj__{(Obj_)};                                      \
    Naive_Code __naive_code__ =                                                \
        Naive_Roster::Resolve().Insert(__naive_tobj__);                        \
    if (__naive_code__ != Naive_Code_ok) {                                     \
      return __naive_code__;                                                   \
    }                                                                          \
    (Tag_) = __naive_tobj__.Tag();                                             \
  } while (0)

#endif
