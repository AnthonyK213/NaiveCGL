#include <naivecgl/Common/Transient.h>

Naive_NAMESPACE_BEGIN(common);

Transient::Transient() : myRefCount_(0) {}

Transient::Transient(const Transient &) : myRefCount_(0) {}

Transient &Transient::operator=(const Transient &) { return *this; }

Transient::~Transient() {}

Transient *Transient::This() const {
  if (GetRefCount() == 0)
    throw ::std::runtime_error("Attempt to create handle to object created in "
                               "stack, not yet constructed, or destroyed");
  return const_cast<Transient *>(this);
}

Naive_NAMESPACE_END(common);
