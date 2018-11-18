/* Intentionally omitting include guard */

/* if this file was re-included with different NDEBUG */
#undef assert

#ifdef NDEBUG
	#define assert(test)     ((void)0)
#else
	/* the function relies on other libc functionality */
	void _Assert(char *);

	/* a "thunk" to evaluate __LINE__ */
	#define _STR(x) _VAL(x)
	#define _VAL(x) #x

	#define assert(test)     ((test) ? (void)0 \
		: _Assert("Assertion failed: " #test \
			", file " __FILE__ ", line " _STR(__LINE__) "\n"))
#endif
