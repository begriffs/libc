CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -Wshadow

.SUFFIXES :
.SUFFIXES : .o .c .h

TESTS = tassert tctype
OBJS = assert.o ctype.o

all :
	ls t*.c | xargs -J % -L 1 basename % .c | xargs ${MAKE}

clean :
	find . -maxdepth 1 -perm -111 -type f -exec rm {} +
	rm -f *.o *.a

assert.o : assert.c assert.h
ctype.o : ctype.c ctype.h

libc.a : $(OBJS)
	ar r $@ $?

.SECONDEXPANSION:

$(TESTS) : $$@.c libc.a
	$(CC) $(CFLAGS) -o $@ $@.c libc.a $(LDFLAGS)
