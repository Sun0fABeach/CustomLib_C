#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "strlib.h"


int main()
{
    assert(startsWith("asdf", "as"));
    assert(startsWith("asdf", "asdf"));
    assert(startsWith("asdf", ""));
    assert(startsWith("", ""));
    assert(!startsWith("asdf", "ax"));
    assert(!startsWith("asdf", "asdf1"));
    assert(!startsWith("", "asdf"));

    assert(endsWith("asdf", "df"));
    assert(endsWith("asdf", "asdf"));
    assert(endsWith("asdf", ""));
    assert(endsWith("", ""));
    assert(!endsWith("asdf", "dx"));
    assert(!endsWith("asdf", "asdfx"));
    assert(!endsWith("", "asdf"));

    char str1[] = "  asdf";
    char str2[] = "asdf";
    char str3[] = "asdf  ";
    assert(trimLeft(str1) == str1 + 2);
    assert(trimLeft(str2) == str2);
    assert(trimLeft(str3) == str3);

    assert(trimRight(str1) == str1);
    assert(strcmp(str1, "  asdf") == 0);
    assert(trimRight(str2) == str2);
    assert(strcmp(str2, "asdf") == 0);
    assert(trimRight(str3) == str3);
    assert(strcmp(str3, "asdf") == 0);

    char str4[] = "  asdf  ";
    assert(trim(str2) == str2);
    char *p = trim(str4);
    assert(p == str4 + 2);
    assert(strcmp(p, "asdf") == 0);


	exit(EXIT_SUCCESS);
}
