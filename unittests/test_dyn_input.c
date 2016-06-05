#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dyn_input.h"


int main()
{
    FILE *const fp = fopen("unittests/sample.txt", "r");

    char *const buf = fBufRead(fp);
    assert(strcmp(buf, "test line bufread") == 0);


    assert(num_strings() == 0);

    char *line = fReadLine(fp);
    assert(strcmp(line, "test line readline1") == 0);
    assert(num_strings() == 1);

    line = fReadLine(fp);
    assert(strcmp(line, "test line readline2") == 0);
    assert(num_strings() == 2);

    assert(clearStrings() == 2);
    assert(num_strings() == 0);

    line = fReadLine(fp);
    assert(strcmp(line, "test line readline3") == 0);
    assert(num_strings() == 1);

    fclose(fp);


	exit(EXIT_SUCCESS);
}
