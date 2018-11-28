CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -Wshadow

.SUFFIXES :
.SUFFIXES : .o .c .h

TESTS = tassert tctype terrno tsetjmp tsignal
OBJS = assert.o ctype.o errno.o

all : $(TESTS)

clean :
	find . -maxdepth 1 -perm -111 -type f -exec rm {} +
	rm -f *.o *.a

assert.o : assert.c assert.h
ctype.o : ctype.c ctype.h
errno.o : errno.c errno.h yvals.h

libc.a : $(OBJS)
	ar r $@ $?

.SECONDEXPANSION:

$(TESTS) : $$@.c libc.a
	$(CC) $(CFLAGS) -o $@ $@.c libc.a $(LDFLAGS)
