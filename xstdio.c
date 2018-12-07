#include "stdio.h"
#include "xstdio.h"

/* stderr buffer */
static unsigned char ebuf[80];

static FILE sin;
/* contains non compile-time constant,
   and note that final param is unset
= {
	_MOPENR, 0,
	NULL, NULL, &sin._Cbuf,
	&sin._Cbuf, NULL, &sin._Cbuf,
};
*/

static FILE sout;
/*
= {
	_MOPENW, 1,
	NULL, NULL, &sout._Cbuf,
	&sout._Cbuf, NULL, &sout._Cbuf,
};
*/

static FILE serr;
/*
= {
	_MOPENW|_NNBF, 2,
	ebuf, ebuf + sizeof(ebuf), ebuf,
	ebuf, NULL, ebuf,
};
*/

FILE *_Files[FOPEN_MAX] = {&sin, &sout, &serr};

FILE *_Foprep(const char *name, const char *mods, FILE *fp)
{
	fp->_Handle = -1;
	fp->_Tmpnam = NULL;
	fp->_Buf = NULL;
	fp->_Next = &fp->_Cbuf;
	fp->_Wend = &fp->_Cbuf;
	fp->_Rend = &fp->_Cbuf;
	fp->_Nback = 0;
	fp->_
