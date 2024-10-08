#include <naivecgl/Common/Roster.h>

#include <naivecgl/Interface/NaiveCGL_c_macros.h>

Naive_NAMESPACE_BEGIN(common);

Roster &Roster::Resolve() {
  static Roster aRoster{};
  return aRoster;
}

Naive_Tag Roster::NewTag() { return ++myTail; }

Naive_Code Roster::Insert(const TObject &theObj) {
  Naive_Tag aTag = theObj.Tag();

  if (aTag == Naive_Object_null)
    return Naive_Code_err;

  auto anIter = myTable.find(aTag);
  if (anIter == myTable.cend())
    myTable.insert(::std::make_pair(aTag, theObj));

  return Naive_Code_ok;
}

Naive_Code Roster::Erase(Naive_Tag theTag) {
  TObject anObj;
  Naive_Code aCode = Find(theTag, anObj);
  if (aCode != Naive_Code_ok)
    return aCode;

  if (anObj.GetRefCount() > 1)
    return Naive_Code_still_referenced;

  anObj.Delete();
  myTable.erase(theTag);
  return Naive_Code_ok;
}

Naive_Code Roster::Find(Naive_Tag theTag, TObject &theObj) const {
  auto anIter = myTable.find(theTag);
  if (anIter == myTable.cend() || anIter->second.IsNull())
    return Naive_Code_invalid_tag;
  theObj = anIter->second;
  return Naive_Code_ok;
}

Roster::Roster() : myTail(0), myTable() {}

Naive_NAMESPACE_END(common);
