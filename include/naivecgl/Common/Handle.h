#ifndef _NaiveCGL_Common_Handle_HeaderFile
#define _NaiveCGL_Common_Handle_HeaderFile

#include "Transient.h"

Naive_NAMESPACE_BEGIN(common);

class Transient;

template <typename T> class handle {
public:
  handle() : myEntity(nullptr) {}

  handle(const T *thePtr) : myEntity(const_cast<T *>(thePtr)) { beginScope(); }

  handle(const handle &theHandle) : myEntity(theHandle.myEntity) {
    beginScope();
  }

  handle(handle &&theHandle) : myEntity(theHandle.myEntity) {
    theHandle.myEntity = nullptr;
  }

  ~handle() { endScope(); }

  void Nullify() { endScope(); }

  Naive_Bool IsNull() const { return myEntity == nullptr; }

  void reset(T *thePtr) { assign(thePtr); }

  handle &operator=(const handle &theHandle) {
    assign(theHandle.myEntity);
    return *this;
  }

  handle &operator=(handle &&theHandle) noexcept {
    ::std::swap(myEntity, theHandle.myEntity);
    return *this;
  }

  handle &operator=(const T *thePtr) {
    assign(const_cast<T *>(thePtr));
    return *this;
  }

  T *get() const { return static_cast<T *>(myEntity); }

  T *operator->() const { return static_cast<T *>(myEntity); }

  T &operator*() const { return *get(); }

  template <typename T1>
  Naive_Bool operator==(const handle<T1> &theHandle) const {
    return get() == theHandle.get();
  }

  template <typename T1> Naive_Bool operator==(const T1 *thePtr) const {
    return get() == thePtr;
  }

  template <typename T1>
  friend Naive_Bool operator==(const T1 *left, const handle &right) {
    return left == right.get();
  }

  template <typename T1>
  Naive_Bool operator!=(const handle<T1> &theHandle) const {
    return get() != theHandle.get();
  }

  template <typename T1> Naive_Bool operator!=(const T1 *thePtr) const {
    return get() != thePtr;
  }

  template <typename T1>
  friend Naive_Bool operator!=(const T1 *left, const handle &right) {
    return left != right.get();
  }

  template <typename T1>
  Naive_Bool operator<(const handle<T1> &theHandle) const {
    return get() < theHandle.get();
  }

  template <typename T1> static handle DownCast(const handle<T1> &theHandle) {
    return handle(dynamic_cast<T *>(const_cast<T1 *>(theHandle.get())));
  }

  template <typename T1> static handle DownCast(const T1 *thePtr) {
    return handle(dynamic_cast<T *>(const_cast<T1 *>(thePtr)));
  }

  explicit operator bool() const { return myEntity != nullptr; }

private:
  void assign(Transient *thePtr) {
    if (thePtr == myEntity)
      return;
    endScope();
    myEntity = thePtr;
    beginScope();
  }

  void beginScope() {
    if (myEntity)
      myEntity->IncrementRefCounter();
  }

  void endScope() {
    if (myEntity && myEntity->DecrementRefCounter() == 0)
      myEntity->Delete();
    myEntity = nullptr;
  }

  template <typename T1> friend class handle;

private:
  Transient *myEntity;
};

Naive_NAMESPACE_END(common);

template <typename T> using Naive_Handle = ::naivecgl::common::handle<T>;

namespace std {

template <typename TheTransientType>
struct hash<Naive_Handle<TheTransientType>> {
  size_t
  operator()(const Naive_Handle<TheTransientType> &theHandle) const noexcept {
    return static_cast<size_t>(
        reinterpret_cast<::std::uintptr_t>(theHandle.get()));
  }
};

} // namespace std

Naive_DEFINE_HANDLE(Naive_Transient);

#endif
