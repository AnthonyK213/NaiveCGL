#ifndef _NaiveCGL_Common_Macro_HeaderFile
#define _NaiveCGL_Common_Macro_HeaderFile

#ifndef Naive_EXPORT
#ifdef _WIN32
#define Naive_EXPORT __declspec(dllexport)
#else
#define Naive_EXPORT
#endif
#endif

#define Naive_NAMESPACE_BEGIN(ns)                                              \
  namespace naivecgl {                                                         \
  namespace ns {
#define Naive_NAMESPACE_END(ns)                                                \
  }                                                                            \
  }

#define Naive_WHERE_IS_REF_OF(T, R)                                            \
  typename ::std::enable_if<                                                   \
      ::std::is_same<typename ::std::remove_reference<T>::type, R>::value,     \
      void>::type

#define Naive_DEFINE_HANDLE(T) using Handle_##T = ::naivecgl::common::handle<T>

#define Naive_True true
#define Naive_False false

#define Naive_TODO throw ::std::runtime_error("Not implemented")

#define Naive_OVERRIDE override

#endif
