#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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

bool isZero(const void *num)
{
    return *(int *)num == 0;
}


int main()
{
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    /* MAP */

    map(a, sizeof(int), 10, square);
    for(int i = 0; i < 10; ++i) {
        assert(a[i] == i * i);
        a[i] = i;  // reset
    }

    /* REDUCE */

    int base = 10;
    reduce(a, &base, sizeof(int), 10, add);
    assert(base == 10+1+2+3+4+5+6+7+8+9);

    const int findable_value = 3;
    const int unfindable_value = 99;

    /* INDEXOF */

    assert(indexOf(a, &findable_value, sizeof(int), 10) == 3);
    assert(indexOf(a, &unfindable_value, sizeof(int), 10) == -1);

    /* CONTAINS */

    assert(contains(a, &findable_value, sizeof(int), 10));
    assert(!contains(a, &unfindable_value, sizeof(int), 10));

    /* SELECT/REJECT */

    int b[10] = {0};
    assert(reject(b, sizeof(int), 10, isZero) == 0);  // full reject
    assert(select(b, sizeof(int), 10, isZero) == 10); // full select
    for(int i = 0; i < 10; ++i) {
        assert(b[i] == 0);
    }

    b[9] = 1;
    assert(select(b, sizeof(int), 10, isZero) == 9); // all but last
    assert(reject(b, sizeof(int), 10, isZero) == 1); // none but last
    assert(b[0] == 1);
    // 1 @ index: 0, 9
    assert(reject(b, sizeof(int), 10, isZero) == 2); // first and last
    assert(b[0] == 1);
    assert(b[1] == 1);
    // 1 @ index: 0, 1, 9
    assert(select(b, sizeof(int), 10, isZero) == 7); // one large mid section
    for(int i = 0; i < 7; ++i) {
        assert(b[i] == 0);
    }
    b[1] = 1;
    b[8] = 1;
    // 1 @ index: 1, 8, 9
    assert(reject(b, sizeof(int), 10, isZero) == 3); // second and last two
    for(int i = 0; i < 3; ++i) {
        assert(b[i] == 1);
    }
    b[5] = 1;
    b[6] = 1;
    // 1 @ index: 0, 1, 2, 5, 6, 8, 9
    assert(select(b, sizeof(int), 10, isZero) == 3); // scattered, not starting
    for(int i = 0; i < 3; ++i) {                     // at array onset
        assert(b[i] == 0);
    }
    // 1 @ index: 5, 6, 8, 9
    assert(select(b, sizeof(int), 10, isZero) == 6); // scattered, starting
    for(int i = 0; i < 6; ++i) {                     // at array onset
        assert(b[i] == 0);
    }

	exit(EXIT_SUCCESS);
}
