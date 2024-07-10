#ifndef _NaiveCGL_Common_Roster_HeaderFile
#define _NaiveCGL_Common_Roster_HeaderFile

#include "Handle.h"

#include <atomic>

Naive_NAMESPACE_BEGIN(common);

class TObject;

class Roster final {
public:
  static Roster &Resolve();

  Naive_Tag NewTag();

  /// For C API only.

  Naive_Code Insert(const Naive_Handle<TObject> &theObj);

  Naive_Code Erase(Naive_Tag theTag);

  Naive_Code Find(Naive_Tag theTag, Naive_Handle<TObject> &theObj) const;

  ///

private:
  Roster();

private:
  ::std::atomic<Naive_Integer> myTail;
  Naive_Hash<Naive_Tag, Naive_Handle<TObject>> myTable;
};

Naive_NAMESPACE_END(common);

using Naive_Roster = ::naivecgl::common::Roster;

#endif