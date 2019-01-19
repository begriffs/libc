#include "assert.h"
#include "ctype.h"
#include "errno.h"
#include "locale.h"
#include "stdlib.h"

#include <limits.h>
#include <math.h>
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
	const char *scan, *sd, *s1, *s2;
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
	for (s2 = scan; (sd = memchr(digits, tolower(*scan), base)) != NULL; ++scan)
	{
		old_x = x; /* for overflow check later */
		x = x*base + (sd - digits);
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
	/* what does x-scan[-1] even mean? Wouldn't that be like 345345 - '5' ? */
	else if (0 < n || x < x - scan[-1] ||
			 (x - scan[-1]) / base != old_x)
	{
		errno = ERANGE;
		x = ULONG_MAX;
	}

	/* Wait, doesn't this function return *unsigned* long?
	   Yes, but we can cast to a signed value in calling functions. */
	if (sign == '-')
		x = -x;

	if (endptr)
		*endptr = (char *)scan;
	return x;
}

/* if it overflows, this will return (int)ULONG_MAX == -1.
   These atox functions are kind of garbage anyhow. */
int (atoi)(const char *s)
{
	return (int)_Stoul(s, NULL, 10);
}

long (atol)(const char *s)
{
	return (long)_Stoul(s, NULL, 10);
}

unsigned long (strtoul)(const char *s, char **endptr, int base)
{
	return _Stoul(s, endptr, base);
}

/* this one is tricky, read carefully */
long (strtol)(const char *s, char **endptr, int base)
{
	const char *sc;
	unsigned long x;

	/* sc will test for -/+ since _Stroul can encode
	   a signed value in an unsigned type */
	for (sc = s; isspace(*sc); ++sc)
		;
	/* s, not sc! */
	x = _Stoul(s, endptr, base);

	/* a negative long considered as unsigned will ordinarily be "greater"
	   than LONG_MAX, and anything "smaller" indicates overflow. */
	if (*sc == '-' && x <= LONG_MAX)
	{
		errno = ERANGE;
		x = LONG_MIN;
	}
	else if (*sc != '-' && x > LONG_MAX)
	{
		errno = ERANGE;
		x = LONG_MAX;
	}

	return (long)x;
}

/*
  Started working on this but it pulls in tons of internal deps
  from the xmath.h section, not available in the public interface
  from <math.h>. Too much work for now until I study floating
  point specifically.

double _Dtento(double x, short n)
{
	double factor;
	short errx;
	size_t i;
	static const double pows[] =
		{ 1e1, 1e2, 1e4, 1e16, 1e32 };
	static const size_t npows = sizeof pows / sizeof pows[0] - 1;

	if (n == 0 || x == 0.0)
		return x;
	factor = 1.0;

	if (n < 0)
	{
		unsigned int nu = -(unsigned int)n;

		for (i = 0; i < nu && i < npows; nu >>= 1. ++i)
		{
			
		}
	}
}
*/

/* limit significant digits (must be divisible by 8) */
#define SIG_MAX 32

double (_Stod)(const char *s, char **endptr)
{
	const char pointchr = localeconv()->decimal_point[0];
	const char *scan;
	/* buf is an array of integer bytes, not treated as
	   ascii characters */
	char buf[SIG_MAX], sign;
	double x;
	int ndigit, nsig, nzero, olead, opoint;

	for (scan = s; isspace(*scan); ++scan)
		;
	sign = *scan == '-' || *scan == '+' ? *scan++ : '+';
	olead  = opoint = -1;

	/* loop until non-digit or duplicate decimal point */
	for (ndigit = nsig = nzero = 0; ; ++scan)
	{
		if (*scan == pointchr)
		{
			/* if decimal point was already seen */
			if (0 <= opoint)
				break;
			else
				opoint = ndigit;
		}
		else if (*scan == '0')
			++nzero, ++ndigit;
		else if (!isdigit(*scan))
			break;
		else
		{
			if (olead < 0)
				olead = ndigit;
			else
				/* buffer zeros so far */
				for (; 0 < nzero && nsig < SIG_MAX; --nzero)
					buf[nsig++] = 0;
			++ndigit;
			if (nsig < SIG_MAX)
				buf[nsig++] = *scan - '0';
		}
	}

	if (0 == ndigit)
	{
		if (endptr)
			*endptr = (char *)s;
		return 0.0;
	}

	/* disregard trailing zeros (they will be reflected
	   in a bigger exponent later) */
	for (; 0 < nsig && buf[nsig-1] == 0; --nsig)
		;

	{ /* compute significand */
		const char *pc = buf;
		int n;
		/* a rollup of eight digits at a time */
		long lo[SIG_MAX/8+1];
		/* pl reads each chunk backwards */
		long *pl = &lo[nsig >> 3];
		static double fac[] = {0, 1e8, 1e16, 1e24, 1e32};

		/* fill pl */
		for (*pl = 0, n = nsig; 0 < n; --n)
		{
			/* reset every eight digits */
			if ((n & 07) == 0)
				*--pl = *pc++;
			else
				*pl = *pl * 10 + *pc++;
		}

		/* Assemble chunks into value. fac[0] == 0 so it
		   doesn't double-count on the first iteration */
		for (x = (double)lo[0], n=0; ++n <= (nsig >> 3); )
			if (lo[n] != 0)
				x += fac[n] * (double)lo[n];
	}

	{ /* adjust with any explicit exponent */
		long lexp = 0;
		short sexp;

		if (*scan == 'e' || *scan == 'E')
		{
			const char *scsav = scan;
			/* the following is safe because || evaluates
			   its left arg before right */
			const char esign =
				*++scan == '-' || *scan == '+'
				? *scan++ : '+';
			if (!isdigit(*scan))
				scan = scsav;
			else
			{
				for (; isdigit(*scan); ++scan)
					if (lexp < 100000)
						lexp = lexp * 10 + *scan - '0';
				if (esign == '-')
					lexp = -lexp;
			}
		}

		if (endptr)
			*endptr = (char *)scan;
		/* if there was no decimal point then adjust lexp
		   for trailing zeros we skipped earlier */
		if (opoint < 0)
			lexp += ndigit - nsig;
		else
			lexp += opoint - olead - nsig;
		
		/* truncate lexp within [SHRT_MIN..SHRT_MAX] */
		sexp = lexp < SHRT_MIN
			? SHRT_MIN
			: lexp < SHRT_MAX
				? (short)lexp
				: SHRT_MAX;

		/* calculate x*(10**sexp), avoiding (over|under)flow
		   the book used an internal function like this:
		   x = _Dtento(x, sexp);
		   but it's intense, so I'm using math.h, screw it. */
		x = x*pow(10, sexp);
	}
	return sign == '-' ? -x : x;
}

