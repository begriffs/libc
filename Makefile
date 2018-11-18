CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -Wshadow

.SUFFIXES :
.SUFFIXES : .o .c .h

# cannot use VPATH - http://austingroupbugs.net/view.php?id=766

assert.o : assert.c assert.h

tassert : tassert.c assert.o
	$(CC) $(CFLAGS) -o $@ tassert.c assert.o $(LDFLAGS)
