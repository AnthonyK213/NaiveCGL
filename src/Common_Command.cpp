#include <naivecgl/Common/Command.h>

Naive_NAMESPACE_BEGIN(common);

Command::~Command() {}

Naive_Code Command::Status() const { return myStatus; }

Command::Command() : myStatus(Naive_Code_initialized) {}

void Command::SetStatus(Naive_Code theStatus) { myStatus = theStatus; }

void Command::ResetStatus() { SetStatus(Naive_Code_initialized); }

void Command::Done() { SetStatus(Naive_Code_ok); }

Naive_NAMESPACE_END(common);
