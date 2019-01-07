#ifndef STRING_H
#define STRING_H

#ifndef _YVALS
#define _YVALS
#include "yvals.h"
#endif

#define NULL _NULL
typedef _Sizet size_t;

void *memchr(const void *, int, size_t);
int   memcmp(const void *, const void *, size_t);
void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);

char   *strcat (char *, const char *);
char   *strncat(char *, const char *, size_t);
char   *strchr (const char *, int);
int     strcmp (const char *, const char *);
int     strncmp(const char *, const char *, size_t);
size_t  strlen (const char *);
int     strcoll(const char *, const char *);
char   *strcpy (char *, const char *);
char   *strncpy(char *, const char *, size_t);
char   *strpbrk(const char *, const char *);
char   *strrchr(const char *, int);
size_t  strspn (const char *, const char *);
size_t  strcspn(const char *, const char *);
char   *strstr (const char *, const char *);
char   *strtok (char *, const char *);
size_t  strxfrm(char *, const char *, size_t);

char *_Strerror(int, char *);

#define sterror(errcode) _Strerror(errcode, NULL)

#endif
