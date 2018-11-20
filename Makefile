CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -Wshadow

.SUFFIXES :
.SUFFIXES : .o .c .h

TESTS = tassert
OBJS = assert.o ctype.o

assert.o : assert.c assert.h
ctype.o : ctype.c ctype.h

libc.a : $(OBJS)
	ar r $@ $?

$(TESTS) : $$@.c libc.a
	$(CC) $(CFLAGS) -o $@ $@.c libc.a $(LDFLAGS)
