#include "string.h"
#include <stdlib.h>

void *(memchr)(const void *s, int c, size_t n)
{
	const unsigned char *sc;

	for (sc = s; 0 < n; ++sc, --n)
		if (*sc == c)
			return (void *)sc;
	return NULL;
}

int (memcmp)(const void *s, const void *t, size_t n)
{
	const unsigned char *su, *tu;
	for (su = s, tu = t; n > 0; --n)
		if (*su != *tu)
			return *su < *tu ? -1 : 1;
	return 0;
}

void *(memcpy)(void *d, const void *s, size_t n)
{
	char *ds = d;
	const char *ss = s;
	while (n-- > 0)
		*ds++ = *ss++;
	return d;
}

void *(memmove)(void *d, const void *s, size_t n)
{
	char *ds = d;
	const char *ss = s;

	/* UB unless d and s are part of the same data object, but
	 * then again, why would the caller be concerned about overlap
	 * if entirely separate objects? */
	if (s > d)
		while (n-- > 0)
			*ds++ = *ss++;
	else
		for (ss += n, ds += n; 0 < n; --n)
			*ds-- = *ss--;
		
	return d;
}

void *(memset)(void *p, int v, size_t n)
{
	unsigned char *pu = p;
	while (n-- > 0)
		*pu++ = (unsigned char)v;

	return p;
}

char *(strcat)(char *d, const char *s)
{
	char *d1;
	for (d1 = d; *d1; ++d1)
		;
	while ((*d1 = *s) != '\0')
		d1++, s++;
	return d;
}

char *(strncat)(char *d, const char *s, size_t n)
{
	char *d1;
	for (d1 = d; *d1; ++d1)
		;
	while (n-- > 0 && (*d1 = *s) != '\0')
		d1++, s++;
	*d1 = '\0';
	return d;
}

char *(strchr)(const char *s, int c)
{
	for (; *s != c; s++)
		if (*s == '\0')
			return NULL;
	return (char *)s;
}

int (strcmp)(const char *s, const char *t)
{
	for ( ; *s == *t; ++s, ++t)
		if (!*s) /* thus !t as well */
			return 0;
	return (*(unsigned char*)s < *(unsigned char*)t)
		? -1 : 1;
}

int (strncmp)(const char *s, const char *t, size_t n)
{
	for ( ; n-- > 0 && *s == *t; ++s, ++t)
		if (!*s) /* thus !t as well */
			return 0;
	return (*(unsigned char*)s < *(unsigned char*)t)
		? -1 : 1;
}

char *(strcpy)(char *d, const char *s)
{
	char *ret = d;
	while ( (*d++ = *s++) )
		;
	return ret;
}

char *(strncpy)(char *d, const char *s, size_t n)
{
	char *ret = d;
	while (n-- > 0 && (*d++ = *s++))
		;
	return ret;
}

char *(strpbrk)(const char *s, const char *keys)
{
	const char *k = keys;
	for ( ; *s; ++s)
		for (k = keys; *k; ++k)
			if (*s == *k)
				return (char *)s;
	return NULL;
}

char *(strrchr)(const char *s, int c)
{
	char *ret = NULL;
	for ( ; *s; ++s)
		if (c == *s)
			ret = (char *)s;
	return ret;
}

size_t (strcspn)(const char *s, const char *keys)
{
	size_t i;
	const char *k;
	for (i = 0; s[i]; ++i)
	{
		for (k = keys; *k; ++k)
			if (s[i] == *k)
				return i;
	}
	return i;
}

size_t (strspn)(const char *s, const char *nono)
{
	size_t i;
	const char *k;
	for (i = 0; s[i]; ++i)
	{
		for (k = nono; *k; ++k)
			if (s[i] == *k)
				break;
		if (!*k)
			break;
	}
	return i;
}

char *(strstr)(const char *s, const char *t)
{
	const char *p, *q;
	for ( ; *s; ++s)
		for (p = s, q = t; ; )
		{
			if (*++q == '\0')
				return (char *)s;
			else if (*++p != *q)
				break;
		}
	return NULL;
}

char *(strtok)(char *s, const char *delims)
{
	static char *ssave = "";
	char *begin, *end;

	begin = s ? s : ssave;
	begin += strspn(begin, delims);

	if (*begin == '\0')
	{
		ssave = "";
		return NULL;
	}

	end = begin + strcspn(begin, delims);
	if (*end != '\0')
		*end++ = '\0';
	ssave = end;
	return begin;
}

size_t (strlen)(const char *s)
{
	size_t i;
	for (i=0; *s; ++s, ++i)
		;
	return i;
}
