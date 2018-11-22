#include "assert.h"
#include "errno.h"

#include <math.h>
#include <stdio.h>

int main(void)
{
	/* starts as zero */
	assert(0 == errno);
	perror("No error reported as - ");

	/* it's a modifiable Lvalue */
	errno = ERANGE;
	assert(ERANGE == errno);

	perror("Range error reported as -");

	errno = 0;
	assert(0 == errno);
	/* one of the few errors mandated by the standard library */
	(void)sqrt(-1);
	perror("Domain error reported as -");
	assert(EDOM == errno);

	puts("SUCCESS testing <errno.h>");
	return 0;
}
