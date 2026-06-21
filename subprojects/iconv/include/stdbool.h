#ifndef _STDBOOL_H
#define _STDBOOL_H

#if defined(__cplusplus)
  #define __bool_true_false_are_defined 1
#else
  #ifndef bool
    #define bool int
  #endif
  #ifndef false
    #define false 0
  #endif
  #ifndef true
    #define true 1
  #endif
  #define __bool_true_false_are_defined 1
#endif

#endif
