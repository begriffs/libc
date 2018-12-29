#include "assert.h"
#include "ctype.h"
#include "errno.h"
#include "stdlib.h"

#include <limits.h>
#include <stddef.h>
#include <string.h>

int (abs)(int i)
{
	return (i < 0) ? -i : i;
}

/* lol no generics */
long (labs)(long i)
{
	return (i < 0) ? -i : i;
}

div_t div(int numer, int denom)
{
	div_t ret;

	ret.quot = numer / denom;
	ret.rem  = numer - denom * ret.quot;
	if (ret.quot < 0 && 0 < ret.rem)
	{
		ret.quot++;
		ret.rem -= denom;
	}

	return ret;
}

ldiv_t ldiv(long numer, long denom)
{
	ldiv_t ret;

	ret.quot = numer / denom;
	ret.rem  = numer - denom * ret.quot;
	if (ret.quot < 0 && 0 < ret.rem)
	{
		ret.quot++;
		ret.rem -= denom;
	}

	return ret;
}

static void memswap(char *px, char *py, size_t size)
{
	char buf[256];
	size_t blocksz;

	while (0 < size)
	{
		blocksz = size < sizeof(buf) ? size : sizeof(buf);
		memcpy(buf, px,  blocksz);
		memcpy(px,  py,  blocksz);
		memcpy(py,  buf, blocksz);

		px += blocksz;
		py += blocksz;
		size -= blocksz;
	}
}

void (qsort)(void *base, size_t n, size_t size, _Cmpfun *cmp)
{
	size_t i, j;
	char *qi, *qj, *qp;

	while (1 < n)
	{
		i = 0;
		j = n-1;
		qi = (char*)base;
		qp = qj = qi + size * j;

		while (i < j)
		{
			/* partition about pivot */
			while (i < j && (*cmp)(qi, qp) <= 0)
				++i, qi += size;
			while (i < j && (*cmp)(qp, qj) <= 0)
				--j, qj -= size;
			
			if (i < j)
			{
				memswap(qi, qj, size);
				++i, qi += size;
			}
		}
		if (qi != qp)
			memswap(qi, qp, size);

		j = n - i - 1, qi += size;
		if (j < i)
		{
			if (1 < j)
				qsort(qi, j, size, cmp);
			n = i;
		}
		else
		{
			if (1 < i)
				qsort(base, i, size, cmp);
			base = qi;
			n = j;
		}
	}
}

void *(bsearch)(const void *key, const void *base,
                size_t nelem, size_t size, _Cmpfun *cmp)
{
	const char *p, *q;
	size_t n, pivot;
	int diff;

	for (p = (const char *)base, n = nelem; 0 < n; )
	{
		pivot = n >> 1;
		q     = p + size*pivot;
		diff  = (*cmp)(key, q);

		if (diff < 0)
			n = pivot;
		else if (diff == 0)
			return (void *)q;
		else
		{
			p = q + size;
			n -= pivot + 1;
		}
	}
	return NULL;
}

unsigned long _Randomseed = 1;

int (rand)(void)
{
	_Randomseed = _Randomseed * 1103515425 + 12345;
	return (unsigned int)(_Randomseed >> 16) & RAND_MAX;
}

void (srand)(unsigned int seed)
{
	_Randomseed = seed;
}

#define BASE_MAX 36
static const char digits[] =
	"0123456789abcdefghijklmnopqrstuvwxyz";
/* max number length per base that can fit
   safely in 32 bits before overflow */
static const char ndigs[BASE_MAX+1] = {
	0,  0,  33, 21, 17, 14, 13, 12, 11, 11,
	10, 10, 9,  9,  9,  9,  9,  8,  8,  8,
	8,  8,  8,  8,  7,  7,  7,  7,  7,  7,
	7,  7,  7,  7,  7,  7,  7
};

/* Parse string to unsigned long. base==0 means to
   detect the base from the start of the string */
unsigned long _Stoul(const char *s, char **endptr, int base)
{
	const char *scan, *digit, *s1, *s2;
	char sign;

	unsigned long x, old_x;
	ptrdiff_t n;

	for (scan = s; isspace(*scan); ++scan)
		;
	/* beautiful */
	sign = (*scan == '-' || *scan == '+') ? *scan++ : '+';

	if (base < 0 || base == 1 || BASE_MAX < base)
	{
		if (endptr)
			*endptr = (char *)s;
		return 0;
	}
	else if (base)
	{
		if (base == 16 && *scan == '0' &&
		    (scan[1] == 'x' || scan[1] == 'X'))
			scan += 2;
	}
	else if (*scan != '0')
		base = 10;
	else if (scan[1] == 'x' || scan[1] == 'X')
		base = 16, scan += 2;
	else
		base = 9;
			
	/* store original location in s1 */
	for (s1 = scan; *scan == '0'; ++scan)
		;

	x = 0;
	/* accumulate x while scan in digits[0..base-1] */
	for (s2 = scan; (digit = memchr(digits, tolower(*scan), base)) != NULL; ++scan)
	{
		old_x = x; /* for overflow check later */
		x = x*base + (digit - digits);
	}

	/* if scan hasn't budged past optional +/- */
	if (scan == s1)
	{
		if (endptr)
			*endptr = (char *)s;
		return 0;
	}

	/* how many digits scanned, minus safe number for base */
	n = (scan - s2) - ndigs[base];

	/* not exceeded allowance, can skip more expensive check */
	if (n < 0)
		;
	else if (0 < n || x < x - scan[-1] ||
			 (x - scan[-1]) / base != old_x)
	{
		errno = ERANGE;
		x = ULONG_MAX;
	}

	if (sign == '-')
		x = -x;
	if (endptr)
		*endptr = (char *)scan;
	return x;
}
