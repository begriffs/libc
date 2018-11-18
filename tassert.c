#define NDEBUG
#include "assert.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


static int val = 0;

static void field_abort(int sig)
{
	(void)sig; /* sig is unused */

	if (val == 1)
	{
		puts("SUCCESS testing <assert.h>");
		exit(EXIT_SUCCESS);
	}
	else
	{
		puts("FAILURE testing <assert.h>");
		exit(EXIT_FAILURE);
	}
}

static void dummy()
{
	int i = 0;
	(void)i; /* i (should be) unused */

	/* NDEBUG is defined here, no abort */
	assert(i == 0);
	assert(i == 1);
}

#undef NDEBUG
#include "assert.h"

int main(void)
{
	assert(signal(SIGABRT, &field_abort) != SIG_ERR);

	/* should not abort, or val would be 0 */
	dummy();

	assert(val == 0);
	++val;

	fputs("Assertion should appear below --\n", stderr);
	assert(val == 0);

	fputs("FAILURE, should not have reached here", stderr);
	exit(EXIT_FAILURE);
}
