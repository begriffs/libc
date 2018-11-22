#ifndef _ERRNO
#define _ERRNO

/* the actual values are system-dependent,
 * so parameterizing them in this helper header. */
#ifndef _YVALS
#include "yvals.h"
#endif

#define EDOM   _EDOM
#define ERANGE _ERANGE

/* using an actual data object, although some
 * implementations make this a macro like (*_Error()) */
extern int errno;

#endif
