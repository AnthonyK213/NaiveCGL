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

Naive_Bool ClassType::IsSubClass(const Naive_Class theClass) const {
  if (myClass == theClass)
    return Naive_True;

  return !mySuper.IsNull() && mySuper->IsSubClass(theClass);
}

ClassType::~ClassType() {
  ClassType::Registry &aRegistry = getRegistry();
  aRegistry.erase(myClass);
}

Handle_Naive_ClassType
ClassType::Register(const ::std::type_info &theInfo, const Naive_Class theClass,
                    const Naive_Size theSize,
                    const Naive_Handle<ClassType> &theSuper) {
  static ::std::mutex theMutex{};
  ::std::lock_guard aGuard(theMutex);

  auto &aRegistry = getRegistry();
  auto anIter = aRegistry.find(theClass);
  if (anIter != aRegistry.end())
    return anIter->second;

  ClassType *aClass = new ClassType(theInfo, theClass, theSize, theSuper);

  aRegistry.emplace(theClass, aClass);
  return aClass;
}

ClassType::ClassType(const ::std::type_info &theInfo,
                     const Naive_Class theClass, const Naive_Size theSize,
                     const Naive_Handle<ClassType> &theSuper)
    : myInfo(theInfo), myClass(theClass), mySize(theSize), mySuper(theSuper) {}

ClassType::Registry &ClassType::getRegistry() {
  static ClassType::Registry aRegistry{};
  return aRegistry;
}

Naive_NAMESPACE_END(common);
