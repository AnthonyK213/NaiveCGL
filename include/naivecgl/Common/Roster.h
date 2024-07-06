#ifndef _NaiveCGL_Common_Roster_HeaderFile
#define _NaiveCGL_Common_Roster_HeaderFile

#include "Macro.h"
#include "Type.h"

#include <atomic>

Naive_NAMESPACE_BEGIN(common);

class Roster {
public:
  static Roster &Resolve();

  Naive_Tag NewTag();

private:
  Roster();

private:
  ::std::atomic<Naive_Integer> myTail;
};

Naive_NAMESPACE_END(common);

using Naive_Roster = ::naivecgl::common::Roster;

#endif
