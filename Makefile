CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -Wshadow

.SUFFIXES :
.SUFFIXES : .o .c .h

TESTS = tassert tctype terrno tsetjmp tsignal tstdarg
OBJS = assert.o ctype.o errno.o stdlib.o

all : $(TESTS)

clean :
	find . -maxdepth 1 -perm -111 -type f -exec rm {} +
	rm -f *.o *.a

assert.o : assert.c assert.h
ctype.o : ctype.c ctype.h
errno.o : errno.c errno.h yvals.h
# stdio.o : stdio.c stdio.h yvals.h xstdio.o
# xstdio.o : xstdio.c xstdio.h
stdlib.o : stdlib.c stdlib.h

tstdarg : stdarg.h yvals.h

libc.a : $(OBJS)
	ar r $@ $?

.SECONDEXPANSION:

$(TESTS) : $$@.c libc.a
	$(CC) $(CFLAGS) -o $@ $@.c libc.a $(LDFLAGS)
