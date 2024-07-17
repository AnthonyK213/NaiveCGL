#include <naivecgl/Common/ClassType.h>

#include <mutex>

Naive_NAMESPACE_BEGIN(common);

Naive_IMPLEMENT_RTTI(ClassType);

Naive_Bool
ClassType::IsSubClass(const Naive_Handle<ClassType> &theClass) const {
  if (theClass.IsNull())
    return Naive_False;

  if (theClass == this)
    return Naive_True;

  return !mySuper.IsNull() && mySuper->IsSubClass(theClass);
}

ClassType::~ClassType() {}

Handle_Naive_ClassType
ClassType::Register(const ::std::type_info &theInfo, const Naive_Size theSize,
                    const Naive_Handle<ClassType> &theSuper) {
  static ::std::mutex theMutex{};
  ::std::lock_guard aGuard(theMutex);

  auto &aRegistry = getRegistry();
  ::std::type_index anIndex(theInfo);
  auto anIter = aRegistry.find(anIndex);
  if (anIter != aRegistry.end())
    return anIter->second;

  Handle_Naive_ClassType aClass = new ClassType(theInfo, theSize, theSuper);

  aRegistry.emplace(anIndex, aClass);
  return aClass;
}

ClassType::ClassType(const ::std::type_info &theInfo, const Naive_Size theSize,
                     const Naive_Handle<ClassType> &theSuper)
    : myIndex(theInfo), mySize(theSize), mySuper(theSuper) {}

ClassType::Registry &ClassType::getRegistry() {
  static ClassType::Registry aRegistry{};
  return aRegistry;
}

Naive_NAMESPACE_END(common);
