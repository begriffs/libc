#include "errno.h"

/* had it been a macro, although in our case it isn't */
#undef errno

int errno = 0;
