#ifndef _NaiveCGL_Common_Transient_HeaderFile
#define _NaiveCGL_Common_Transient_HeaderFile

#include "Macro.h"
#include "Type.h"

#include <atomic>

Naive_NAMESPACE_BEGIN(common);

class Transient {
public:
  Naive_EXPORT Transient();

  Naive_EXPORT Transient(const Transient &);

  Naive_EXPORT Transient &operator=(const Transient &);

  Naive_EXPORT virtual ~Transient();

  Naive_EXPORT Transient *This() const;

  inline Naive_Integer GetRefCount() const noexcept { return myRefCount_; }

  inline void IncrementRefCounter() noexcept { ++myRefCount_; }

  inline Naive_Integer DecrementRefCounter() noexcept { return --myRefCount_; }

  Naive_EXPORT virtual void Delete() const { delete this; }

protected:
  ::std::atomic<Naive_Integer> myRefCount_;
};

Naive_NAMESPACE_END(common);

using Naive_Transient = ::naivecgl::common::Transient;

#endif
