#include <naivecgl/Common/Command.h>

Naive_NAMESPACE_BEGIN(common);

Command::Command() : myStatus(Naive_Code_initialized) {}

Command::~Command() {}

Naive_Code Command::Status() const { return myStatus; }

Naive_Bool Command::IsDone() const { return myStatus == Naive_Code_ok; }

void Command::Reset() {
  ResetStatus();
  ResetInternal();
}

void Command::SetStatus(Naive_Code theStatus) { myStatus = theStatus; }

void Command::ResetStatus() { SetStatus(Naive_Code_initialized); }

void Command::Done() { SetStatus(Naive_Code_ok); }

void Command::ResetInternal() {}

Naive_NAMESPACE_END(common);
