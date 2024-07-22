#ifndef _NAIVECGL_C_MACROS_H
#define _NAIVECGL_C_MACROS_H

/* Naive_Object_null */

#define Naive_Object_null ((Naive_Object_t)0)

/* Naive_Logical_t */

#define Naive_Logical_true ((Naive_Logical_t)1)
#define Naive_Logical_false ((Naive_Logical_t)0)

/* Naive_Body_boolean_o_m */

#define Naive_Body_boolean_o_m(options)                                        \
  ((options).function = Naive_boolean_unite_c)

#endif
