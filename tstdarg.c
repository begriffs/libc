#include "assert.h"
#include "stdarg.h"

#include <stdio.h>

typedef struct {
	char c;
} Cstruct;

static int tryit(const char *fmt, ...)
{
	int ctr = 0, foo;
	j_va_list ap;

	j_va_start(ap, fmt);
	for (; *fmt; ++fmt)
		switch (*fmt)
		{
			case 'i':
				printf ("%i\n", foo = j_va_arg(ap, int));
				assert(foo == ++ctr);
				break;
			case 'd':
				assert(j_va_arg(ap, double) == ++ctr);
				break;
			case 'p':
				assert(j_va_arg(ap, char*)[0] == ++ctr);
				break;
			case 's':
				assert(j_va_arg(ap, Cstruct).c == ++ctr);
		}
	j_va_end(ap);
	return ctr;
}

int main(void)
{
	Cstruct x = {3};

	assert(tryit("iisdi", '\1', 2, x, 4.0, 5) == 5);
	assert(tryit("") == 0);
	assert(tryit("pdp", "\1", 2.0, "\3") == 3);

	printf("sizeof (va_list) = %lu\n", sizeof (va_list));
	puts("SUCCESS testing <stdarg.h>");

	return 0;
}
