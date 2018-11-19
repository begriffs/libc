#ifndef _CTYPE
#define _CTYPE

/* _Ctype bit flags */

#define _XA 0x200 /* extra alphabetic */
#define _XS 0x100 /* extra space */
#define _BB 0x80  /* BEL, BS, etc */
#define _CN 0x40  /* \n \r \t etc */
#define _DI 0x20  /* digits */
#define _LO 0x10  /* lower case */
#define _PU 0x08  /* punctuation */
#define _SP 0x04  /* space */
#define _UP 0x02  /* uppercase */
#define _XD 0x01  /* hex digit */

/* declarations */

int isalnum(int), isalpha(int), iscntrl(int), isdigit(int);
int isgraph(int), islower(int), isprint(int), ispunct(int);
int isspace(int), isupper(int), isxdigit(int);
int tolower(int), toupper(int);

extern const short *_Ctype, *_Tolower, *_Toupper;

/* macro overrides */

#define isalnum(c)  (_Ctype[(int)(c)] & (_DI|_LO|_UP|_XA))
#define isalpha(c)  (_Ctype[(int)(c)] & (    _LO|_UP|_XA))
#define iscntrl(c)  (_Ctype[(int)(c)] & (_BB|_CN))
#define isdigit(c)  (_Ctype[(int)(c)] & _DI)
#define isgraph(c)  (_Ctype[(int)(c)] & (_DI|_LO|_PU|_UP|_XA))
#define islower(c)  (_Ctype[(int)(c)] & _LO)
#define isprint(c)  (_Ctype[(int)(c)] & (_DI|_LO|_PU|_UP|_XA|_SP))
#define ispunct(c)  (_Ctype[(int)(c)] & _PU)
#define isspace(c)  (_Ctype[(int)(c)] & (_CN|_SP|_XS))
#define isupper(c)  (_Ctype[(int)(c)] & _UP)
#define isxdigit(c) (_Ctype[(int)(c)] & _XD)
#define tolower(c)  _Tolower[(int)(c)]
#define toupper(c)  _Toupper[(int)(c)]

#endif
