#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1
#define _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1

#include <naivecgl/Common/Memory.h>
#include <naivecgl/Interface/NaiveCGL_c.h>

#include <cstdlib>

#define Naive_CHECK_CODE(Code_)                                                \
  do {                                                                         \
    Naive_Code_t __code__ = (Code_);                                           \
    if (__code__ != Naive_Code_ok) {                                           \
      return __code__;                                                         \
    }                                                                          \
  } while (0)

#define Naive_ROSTER_ASK(Tp_, Tag_, Var_)                                      \
  Naive_Handle<Tp_> Var_;                                                      \
  do {                                                                         \
    Naive_TObject __tobj__;                                                    \
    Naive_CHECK_CODE(Naive_Roster::Resolve().Find((Tag_), __tobj__));          \
    Var_ = Naive_Handle<Tp_>::DownCast(__tobj__.GetObject());                  \
    if (!(Var_)) {                                                             \
      return Naive_Code_invalid_object;                                        \
    }                                                                          \
  } while (0)

#define Naive_ROSTER_ADD(Obj_, Tag_)                                           \
  do {                                                                         \
    Naive_TObject __tobj__{(Obj_)};                                            \
    Naive_CHECK_CODE(Naive_Roster::Resolve().Insert(__tobj__));                \
    (Tag_) = __tobj__.Tag();                                                   \
  } while (0)

#define Naive_ALLOC_ARRAY(Tp_, Size_, Var_)                                    \
  Naive_CHECK_CODE(Naive_Memory_alloc(sizeof(Tp_) * (Size_), (void **)(Var_)));

#define Naive_ENUM_CAST(Enum_, Val_, Var_)                                     \
  Enum_ Var_;                                                                  \
  do {                                                                         \
    auto __enum__ = ::naivecgl::common::Enum_##Caster::From(Val_);             \
    if (!__enum__) {                                                           \
      return Naive_Code_invalid_value;                                         \
    }                                                                          \
    Var_ = __enum__.value();                                                   \
  } while (0)

const ::naivecgl::common::MemHandler &Naive_default_mem_handler();

// template <class T> struct Naive_Default_delete {
//   void operator()(T *ptr) const noexcept { Naive_Memory_free(ptr); }
// };

// template <class T>
// using Naive_unique_ptr = ::std::unique_ptr<T, Naive_Default_delete<T>>;

#endif
