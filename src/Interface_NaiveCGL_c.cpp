#include "Interface_NaiveCGL_c.h"

Naive_Hash<Naive_Tag, Handle_Naive_TObject> NAIVE_OBJECT_ROSTER{};

Naive_Code _Naive_Roster_ask(Naive_Tag theTag, Handle_Naive_TObject &theObj) {
  auto anIter = NAIVE_OBJECT_ROSTER.find(theTag);
  if (anIter == NAIVE_OBJECT_ROSTER.cend() || anIter->second.IsNull())
    return Naive_Code_invalid_tag;
  theObj = anIter->second;
  return Naive_Code_ok;
}

Naive_Code _Naive_Roster_add(const Handle_Naive_TObject &theObj) {
  if (theObj.IsNull())
    return Naive_Code_null_arg_address;

  Naive_Tag aTag = theObj->Tag();
  auto anIter = NAIVE_OBJECT_ROSTER.find(aTag);
  if (anIter != NAIVE_OBJECT_ROSTER.cend())
    return Naive_Code_err;

  NAIVE_OBJECT_ROSTER.insert(::std::make_pair(aTag, theObj));
  return Naive_Code_ok;
}

Naive_Code _Naive_Roster_del(Naive_Tag theTag) {
  Handle_Naive_TObject anObj;
  Naive_Code aCode = _Naive_Roster_ask(theTag, anObj);
  if (aCode != Naive_Code_ok)
    return aCode;

  NAIVE_OBJECT_ROSTER[theTag] = nullptr;
  return Naive_Code_ok;
}
