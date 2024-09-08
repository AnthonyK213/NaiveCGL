#ifndef _NaiveCGL_Common_EnumCaster_HeaderFile
#define _NaiveCGL_Common_EnumCaster_HeaderFile

#include "../Interface/NaiveCGL_c_enums.h"

#include "Macro.h"
#include "Type.h"

#include <optional>

Naive_NAMESPACE_BEGIN(common);

template <typename Enum_, int Lower_, int Upper_> class EnumCaster {
public:
  static Naive_Integer To(Enum_ theEnum) {
    return static_cast<Naive_Integer>(theEnum);
  }

  static ::std::optional<Enum_> From(Naive_Integer theInt) {
    if (theInt < Lower_ || theInt > Upper_)
      return ::std::nullopt;
    return static_cast<Enum_>(theInt);
  }
};

/* NOTE: The range of enum needs to be updated after a modification. */

using Naive_AlgorithmCaster = EnumCaster<Naive_Algorithm, 0, 3>;
using Naive_ClassCaster = EnumCaster<Naive_Class, 0, 53>;
using Naive_CodeCaster = EnumCaster<Naive_Code, 0, 26>;
using Naive_Loop_typeCaster = EnumCaster<Naive_Loop_type, 0, 2>;
using Naive_NurbsCurve_formCaster = EnumCaster<Naive_NurbsCurve_form, 0, 6>;
using Naive_NurbsSurface_formCaster = EnumCaster<Naive_NurbsCurve_form, 0, 11>;
using Naive_OrientationCaster = EnumCaster<Naive_Orientation, 0, 3>;
using Naive_boolean_functionCaster = EnumCaster<Naive_boolean_function, 0, 2>;

Naive_NAMESPACE_END(common);

#endif
