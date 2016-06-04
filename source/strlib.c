#include <string.h>
#include <ctype.h>
#include "strlib.h"


bool startsWith(const char *const s, const char *const pattern)
{
    return strstr(s, pattern) == s;
}


bool endsWith(const char *const s, const char *const ending)
{
	const size_t s_len = strlen(s);
	const size_t ending_len = strlen(ending);

	if(ending_len > s_len) return false;
	if(strcmp(s + s_len - ending_len, ending)) return false;
	return true;
}


char *trimLeft(const char *s)
{
	while(isspace(*s)) ++s;
	return (char *)s;
}


char *trimRight(char *s)
{
	char *p = s + strlen(s);
	while(isspace(*--p) && p >= s)
		;
	*(p + 1) = '\0';
	return s;
}
