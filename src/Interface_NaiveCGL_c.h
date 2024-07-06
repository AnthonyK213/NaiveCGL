#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1
#define _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1

#include <naivecgl/Common/TObject.h>
#include <naivecgl/Interface/NaiveCGL_c.h>

#define Naive_ROSTER_ASK(T, Tag, Var)                                          \
  Naive_Handle<T> Var;                                                         \
  do {                                                                         \
    Handle_Naive_TObject __naive_tobj__;                                       \
    Naive_Code __naive_code__ = _Naive_Roster_ask(Tag, __naive_tobj__);        \
    if (__naive_code__ != Naive_Code_ok) {                                     \
      return __naive_code__;                                                   \
    }                                                                          \
    Var = Naive_Handle<T>::DownCast(__naive_tobj__);                           \
    if (!Var) {                                                                \
      return Naive_Code_invalid_object;                                        \
    }                                                                          \
  } while (0)
#define Naive_ROSTER_ADD(Obj)                                                  \
  do {                                                                         \
    Naive_Code __naive_code__ = _Naive_Roster_add(Obj);                        \
    if (__naive_code__ != Naive_Code_ok) {                                     \
      return __naive_code__;                                                   \
    }                                                                          \
  } while (0)

Naive_Code _Naive_Roster_ask(Naive_Tag theTag, Handle_Naive_TObject &theObj);
Naive_Code _Naive_Roster_add(const Handle_Naive_TObject &theObj);
Naive_Code _Naive_Roster_del(Naive_Tag theTag);

#endif
