#include <naivecgl/BRepAPI/Command.h>

Naive_NAMESPACE_BEGIN(brepapi);

Command::~Command() {}

Naive_Code Command::Status() const { return myStatus; }

Command::Command() : myStatus(Naive_Code_initialized) {}

void Command::SetStatus(Naive_Code theStatus) { myStatus = theStatus; }

Naive_NAMESPACE_END(brepapi);