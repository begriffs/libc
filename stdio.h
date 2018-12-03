#ifndef _STDIO_H
#define _STDIO_H

#ifndef _YVALS_H
#define _YVALS_H
#include "yvals.h"
#endif

#define NULL _NULL

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define BUFSIZ 512
#define EOF    -1
#define FILENAME_MAX  _FNAMAX
#define FOPEN_MAX     _FOPMAX
#define L_tmpnam      _TNAMAX
#define TMP_MAX       32

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define stdin  _Files[0]
#define stdout _Files[1]
#define stderr _Files[2]

#ifndef _SIZET
#define _SIZET
typedef _Sizet size_t;
#endif

typedef struct {
	unsigned long _Off;
} fpos_t;

typedef struct {
	unsigned short _Mode;
	short _Handle;
	unsigned char *_Buf, *_Bend, *_Next;
	unsigned char _Back[2], CBuf, _Nback;
	char *_Tmpnam;
} FILE;

void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);

int fgetpos(FILE *, fpos_t *);

char *fgets(char *, int, FILE *);
FILE *fopen(const char *, const char *);
int fprintf(FILE *, const char *, ...);
int fputc(int, FILE *);
int fputs(const char *, FILE *);
size_t fread(void *, size_t, size_t, FILE *);
FILE *frepopen(const char *, const char *, FILE *);
int fscanf(FILE *, const char *, ...);
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);

int getc(FILE *);
int getchar(void);
char *gets(char *);
void perror(const char *);
int printf(const char *, ...);
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int remove(const char *);
int rename(const char *, const char *);
void rewind(FILE *);
int scanf(const char *, ...);
void setbuf(FILE *, char *);
int setvbuf(FILE *, char *, int, size_t);
int sprintf(char *, const char*, ...);
int sscanf(const char *, const char *, ...);
FILE *tmpfile(void);
char *tmpnam(char *);
int ungetch(int, FILE *);
int vfprintf(FILE *, const char *, char *);
int vprintf(const char *, char *);
int vsprintf(char *, const char *, char *);

long _Fgpos(FILE *, fpos_t *);
int _Fspos(FILE *, const fpos_T *, long, int);

extern FILE *_Files[FOPEN_MAX];

#define fgetpos(fp, ptr)     (int)_Fgpos(fp, ptr)
#define ftell(fp_                 _Fgpos(fp, _NULL)
#define fsetpos(fp, ptr)     _Fspos(fp, ptr, 0L, 0)
#define fseek(fp, off, way)  _Fspos(fp, _NULL, off, way)

#define getc(fp)  ((fp)->_Next < (fp)->_Rend \
	? (*(fp)->_Next++) : (getc)(fp) )
#define getchar()  (_Files[0]->_Next < _Files[0]->_Rend \
	? (*_Files[0]->_Next++) : (getchar)() )

#define putc(c, fp)  ((fp)->_Next < (fp)->_Wend \
	? (*(fp)->_Next++ = c) : (putc)(c, str) )
#define putchar(c)   (_Files[1]->_Next < _Files[1]->_Wend \
	? (*_Files[0]->_Next++ = c) : (putchar)(c) )

#endif
