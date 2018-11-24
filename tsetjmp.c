#include "assert.h"

#include <setjmp.h>
#include <stdio.h>

static int ctr;
static jmp_buf b0;

static void jmpto(int n)
{
	longjmp(b0, n);
}

static char *stackptr(void)
{
	char ch;
	return &ch;
}

static int tryit(void)
{
	jmp_buf b1;
	char *sp = stackptr();

	switch (setjmp(b0))
	{
		case 0:
			assert(stackptr() == sp);
			assert(0 == ctr);
			++ctr;
			jmpto(0); /* should translate to 1, not 0 */
		case 1:
			assert(stackptr() == sp);
			assert(1 == ctr);
			++ctr;
			jmpto(2);
		case 2:
			assert(stackptr() == sp);
			assert(2 == ctr);
			++ctr;
			switch (setjmp(b1))
			{
				case 0:
					assert(stackptr() == sp);
					assert(3 == ctr);
					++ctr;
					longjmp(b1, -7);
					break;
				case -7:
					assert(stackptr() == sp);
					assert(4 == ctr);
					++ctr;
					jmpto(3);
				case 5:
					return 13;
				default:
					return 0;
			}
		case 3:
			longjmp(b1, 5);
			break;
	}
	return -1;
}

int main(void)
{
	assert(tryit() == 13);
	printf("sizeof (jmp_buf) = %lu\n", sizeof(jmp_buf));
	puts("SUCCESS testing <setjmp.h>\n");
	return 0;
}
