#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "assert.h"

static int sigs[] = {
	SIGABRT, SIGFPE, SIGILL, SIGINT, SIGINT, SIGSEGV, SIGTERM
};

static void (*rets[])(int) = { SIG_DFL, SIG_ERR, SIG_IGN };
static sig_atomic_t atomic;

static void field_fpe(int sig)
{
	assert(SIGFPE == sig);
	puts("SUCCESS testing <signal.h>");
	exit(EXIT_SUCCESS);
}


int main(void)
{
	printf("sizeof(sig_atomic_t) = %lu\n", sizeof(sig_atomic_t));
	assert(signal(SIGFPE, &field_fpe) == SIG_DFL);
	assert(signal(SIGFPE, &field_fpe) == &field_fpe);
	raise(SIGFPE);
	puts("FAILURE testing <signal.h>");
	return EXIT_FAILURE;
}
