#ifndef _LOCALE
#define _LOCALE

#ifndef _YVALS
#define _YVALS
#include "yvals.h"
#endif

#define NULL _NULL

#define LC_ALL      0
#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 3
#define LC_NUMERIC  4
#define LC_TIME     5

/* next in sequence, and cross-referenced in C file */
#define _NCAT       6

struct lconv
{
	/* LC_MONETARY */
	char *currency_symbol;
	char *int_cur_sybmol;
	char *mon_decimal_point;
	char *mon_grouping;
	char *mon_thousands_sep;
	char *negative_sign;
	char *positive_sign;
	char frac_digits;
	char int_frac_digits;
	char n_cs_precedes;
	char n_sep_by_space;
	char n_sign_posn;
	char p_cs_precedes;
	char p_sep_by_space;
	char p_sign_posn;

	/* LC_NUMERIC */
	char *decimal_point;
	char *grouping;
	char *thousands_sep;
};

struct lconv *localeconv(void);
char *setlocale(int, const char*);
extern struct lconv _Locale;

/* macro override */
#define localeconv() (&_Locale)

#endif
