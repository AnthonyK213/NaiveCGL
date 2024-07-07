#include <naivecgl/Common/Roster.h>
#include <naivecgl/Common/TObject.h>

Naive_NAMESPACE_BEGIN(common);

Roster &Roster::Resolve() {
  static Roster aRoster{};
  return aRoster;
}

Naive_Tag Roster::NewTag() { return ++myTail; }

Naive_Code Roster::Insert(const Naive_Handle<TObject> &theObj) {
  if (theObj.IsNull())
    return Naive_Code_null_arg_address;

  Naive_Tag aTag = theObj->Tag();
  auto anIter = myTable.find(aTag);
  if (anIter != myTable.cend())
    return Naive_Code_err;

  myTable.insert(::std::make_pair(aTag, theObj));
  return Naive_Code_ok;
}

Naive_Code Roster::Erase(Naive_Tag theTag) {
  Handle_Naive_TObject anObj;
  Naive_Code aCode = Find(theTag, anObj);
  if (aCode != Naive_Code_ok)
    return aCode;

  if (anObj->GetRefCount() > 2)
    return Naive_Code_still_referenced;

  myTable[theTag] = nullptr;
  return Naive_Code_ok;
}

Naive_Code Roster::Find(Naive_Tag theTag, Naive_Handle<TObject> &theObj) const {
  auto anIter = myTable.find(theTag);
  if (anIter == myTable.cend() || anIter->second.IsNull())
    return Naive_Code_invalid_tag;
  theObj = anIter->second;
  return Naive_Code_ok;
}

Roster::Roster() : myTail(0), myTable() {}

Naive_NAMESPACE_END(common);
