#ifndef _NaiveCGL_Common_Handle_HeaderFile
#define _NaiveCGL_Common_Handle_HeaderFile

#include "Transient.h"

Naive_NAMESPACE_BEGIN(common);

template <typename T> class Handle {
public:
  Handle() : myEntity(nullptr) {}

  Handle(const T *thePtr) : myEntity(const_cast<T *>(thePtr)) { beginScope(); }

  Handle(const Handle &theHandle) : myEntity(theHandle.myEntity) {
    beginScope();
  }

  Handle(Handle &&theHandle) : myEntity(theHandle.myEntity) {
    theHandle.myEntity = nullptr;
  }

  ~Handle() { endScope(); }

  void Nullify() { endScope(); }

  Naive_Bool IsNull() const { return myEntity == nullptr; }

  void reset(T *thePtr) { assign(thePtr); }

  Handle &operator=(const Handle &theHandle) {
    assign(theHandle.myEntity);
    return *this;
  }

  Handle &operator=(Handle &&theHandle) noexcept {
    std::swap(myEntity, theHandle.myEntity);
    return *this;
  }

  Handle &operator=(const T *thePtr) {
    assign(const_cast<T *>(thePtr));
    return *this;
  }

  T *get() const { return static_cast<T *>(myEntity); }

  T *operator->() const { return static_cast<T *>(myEntity); }

  T &operator*() const { return *get(); }

  template <typename T1>
  Naive_Bool operator==(const Handle<T1> &theHandle) const {
    return get() == theHandle.get();
  }

  template <typename T1> Naive_Bool operator==(const T1 *thePtr) const {
    return get() == thePtr;
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

private:
  Transient *myEntity;
};

Naive_NAMESPACE_END(common);

template <typename T> using Naive_Handle = naivecgl::common::Handle<T>;

#endif
