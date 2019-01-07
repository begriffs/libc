#include "assert.h"
#include "string.h"

#include <stdio.h>

int main(void)
{
	char s[20];

	static const char abcde[] = "abcde";
	static const char abcdx[] = "abcdx";

	assert(memchr(abcde, 'c', 5) == &abcde[2]);
	assert(memchr(abcde, 'e', 4) == NULL);
	assert(memcmp(abcde, abcdx, 5) != 0);
	assert(memcmp(abcde, abcdx, 4) == 0);
	assert(memcpy(s, abcde, 6) == s && s[2] == 'c');
	assert(memmove(s, s+1, 3) == s);
	assert(memcmp(memmove(s, s+1, 3), "aabce", 6));
	assert(memcmp(
		(char*)memmove(s+2, s, 3) - 2,
		"bcece", 6
	));
	assert(memset(s, '*', 10) == s && s[9] == '*');
	assert(memset(s+2, '%', 0) == s+2 && s[2] == '*');
	assert(strcat(memcpy(s, abcde, 6), "fg") == s);
	assert(s[6] == 'g');
	assert(strchr(abcde, 'x') == NULL);
	assert(strchr(abcde, 'c') == &abcde[2]);
	assert(strchr(abcde, '\0') == &abcde[5]);
	assert(strcmp(abcde, abcdx) != 0);
	assert(strcmp(abcde, "abcde") == 0);
	assert(strcpy(s, abcde) == s && strcmp(s, abcde) == 0);
	assert(strcspn(abcde, "xdy") == 3);
	assert(strcspn(abcde, "xzy") == 5);
	assert(strlen(abcde) == 5);
	assert(strlen("") == 0);
	assert(strncat(strcpy(s, abcde), "fg", 1) == s &&
			strcmp(s, "abcdef") == 0);
	assert(strncmp(abcde, "abcde", 30) == 0);
	assert(strncmp(abcde, abcdx, 30) != 0);
	assert(strncmp(abcde, abcdx, 4) == 0);

	assert(strncpy(s, abcde, 7) == s &&
			memcmp(s, "abcde\0", 7) == 0);
	assert(strncpy(s, "xyz", 2) == s &&
			strcmp(s, "xycde") == 0);
	assert(strpbrk(abcde, "xdy") == &abcde[3]);
	assert(strpbrk(abcde, "xyz") == NULL);
	assert(strrchr(abcde, 'x') == NULL);
	assert(strrchr(abcde, 'c') == &abcde[2]);
	assert(strcmp(strrchr("ababa", 'b'), "ba") == 0);
	assert(strspn(abcde, "abce") == 3);
	assert(strspn(abcde, abcde) == 5);

	assert(strstr(abcde, "xyz") == NULL);
	assert(strstr(abcde, "cd") == &abcde[2]);

	assert(strtok(strcpy(s, abcde), "ac") == &s[1]);
	assert(strtok(NULL, "ace") == &s[3]);
	assert(strtok(NULL, "ace") == NULL &&
			memcmp(s, "ab\0d\0\0", 6) == 0);

	puts("SUCCESS testing <string.h>");
	return 0;
}
