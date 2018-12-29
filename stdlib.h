#ifndef STDLIB_H
#define STDLIB_H

#define NULL ((void*)0)
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767

#ifndef _SIZE_T
#define _SIZE_T
	typedef unsigned long size_t;
#endif

typedef struct
{
	int quot;
	int rem;
} div_t;

typedef struct
{
	long quot;
	long rem;
} ldiv_t;

typedef int _Cmpfun(const void *, const void *);

void abort(void);
int abs(int);
int atexit(void (*)(void));
double atof(const char *);
int atoi(const char *);
long atol(const char *);
void *bsearch(const void *, const void *,
              size_t, size_t, _Cmpfun *);
void *calloc(size_t, size_t);
div_t div(int, int);
void exit(int);
void free(void *);
char *getenv(const char *);
long labs(long);
ldiv_t ldiv(long, long);
void *malloc(size_t);
void qsort(void *, size_t, size_t, _Cmpfun *);
int rand(void);
void *realloc(void *, size_t);
void srand(unsigned int);
double strtod(const char *, char **);
long strtol(const char *, char **, int);
unsigned long strtoul(const char *, char **, int);
int system(const char *);

double _Stod(const char *, char **);
unsigned long _Stoul(const char *, char **, int);

extern unsigned long _Randseed;

/* macro overrides */

#define atof(s)                  _Stod(s, NULL)
#define atoi(s)                  (int)_Stoul(s, NULL, 10);
#define atol(s)                  (long)_Stoul(s, NULL, 10);
#define srand(seed)              (void)(_Randseed = (seed))
#define strtod(s, endptr)        _Stod(s, endptr)
#define strtoul(s, endptr, base) _Stoul(s, endptr, base);

#endif
