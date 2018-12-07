#include <stdlib.h>
#include "stdio.h"
#include "xstdio.h"

FILE *(fopen)(const char *name, const char *mods)
{
	FILE *fp;
	size_t i;

	for (i = 0; i < FOPEN_MAX; ++i)
	{
		/* an unallocated slot */
		if (_Files[i] == NULL)
		{
			fp = malloc(sizeof(FILE));
			if (fp == NULL)
				return NULL;
			_Files[i] = fp;
			fp->_Mode = _MALFIL;
			break;
		}
		/* preallocated but unused slot */
		else if (_Files[i]->_Mode == 0)
		{
			fp = _Files[i];
			break;
		}
	}
	if (i >= FOPEN_MAX)
		return NULL;
	return _Foprep(name, mods, fp);
}
