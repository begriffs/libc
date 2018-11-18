#include "assert.h"

#include <stdio.h>
#include <stdlib.h>

void _Assert(char *mesg)
{
	fputs(mesg, stderr);
	abort();
}
