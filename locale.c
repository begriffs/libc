#include "limits.h"
#include "locale.h"

static char null[] = "";

struct lconv _Locale = {
	/* LC_MONETARY */
	null, null,
	null, null,
	null, null,
	null,
	CHAR_MAX, CHAR_MAX,
	CHAR_MAX, CHAR_MAX,
	CHAR_MAX, CHAR_MAX,
	CHAR_MAX, CHAR_MAX,
	/* LC_NUMERIC */
	".",
	null, null
};

/* parens used to cut through macro */
struct lconv *(localeconf)(void)
{
	return &_Locale;
}
