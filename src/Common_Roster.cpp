#include <naivecgl/Common/Roster.h>

Naive_NAMESPACE_BEGIN(common);

Roster &Roster::Resolve() {
  static Roster aRoster{};
  return aRoster;
}

Naive_Tag Roster::NewTag() { return ++myTail; }

Roster::Roster() : myTail(0) {}

Naive_NAMESPACE_END(common);
