#ifndef _NaiveCGL_Common_Roster_HeaderFile
#define _NaiveCGL_Common_Roster_HeaderFile

#include "TObject.h"

#include "../Collection/Hash.h"

Naive_NAMESPACE_BEGIN(common);

class Roster final {
public:
  static Roster &Resolve();

  Naive_Tag NewTag();

  /// For C API only.

  Naive_Code Insert(const TObject &theObj);

  Naive_Code Erase(Naive_Tag theTag);

  Naive_Code Find(Naive_Tag theTag, TObject &theObj) const;

  ///

private:
  Roster();

private:
  ::std::atomic<Naive_Integer> myTail;
  Naive_Hash<Naive_Tag, TObject> myTable;
};

Naive_NAMESPACE_END(common);

using Naive_Roster = ::naivecgl::common::Roster;

#endif
