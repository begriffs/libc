#ifndef _STDARG
#define _STDARG

#ifndef _YVALS
#include "yvals.h"
#endif

typedef char *j_va_list;

#define j_va_start(ap, A) \
  (void)((ap) = (char *)&(A) + _Round(A, _ARGPAD))

#define j_va_end(ap) (void)0

#define j_va_arg(ap, T) \
  (* (T*) ( ((ap) += _Round(T, _ARGPAD)) - \
            _Round(T, _ARGHOLE) ))

/* amt should be a padding value of 2^N - 1 */
#define _Round(X, amt) \
  (sizeof (X) + (amt) & ~(amt))

#endif
