#include <naivecgl/BRepBuilderAPI/Builder.h>
#include <naivecgl/Topology/Body.h>

Naive_NAMESPACE_BEGIN(brepbuilderapi);

Builder::Builder() : common::Command(), myBody(nullptr) {}

Handle_Naive_Body Builder::Body() const {
  return Status() == Naive_Code_ok ? myBody : nullptr;
}

Naive_NAMESPACE_END(brepbuilderapi);
