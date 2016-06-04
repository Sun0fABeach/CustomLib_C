#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "mylib.h"


void square(void *val)
{
    int *casted = (int*)val;
    *casted *= *casted;
}

void add(void *a, void *b)
{
    int *casted_a = (int *)a;
    int *casted_b = (int *)b;
    *casted_a += *casted_b;
}

int main()
{
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    map(a, sizeof(int), 10, square);
    for(int i = 0; i < 10; ++i) {
        assert(a[i] == i * i);
        a[i] = i;  // reset
    }

    int base = 10;
    reduce(a, &base, sizeof(int), 10, add);
    assert(base == 10+1+2+3+4+5+6+7+8+9);

    const int findable_value = 3;
    const int unfindable_value = 99;

    assert(indexOf(a, &findable_value, sizeof(int), 10) == 3);
    assert(indexOf(a, &unfindable_value, sizeof(int), 10) == -1);

    assert(contains(a, &findable_value, sizeof(int), 10));
    assert(!contains(a, &unfindable_value, sizeof(int), 10));

	exit(EXIT_SUCCESS);
}
