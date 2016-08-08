#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

    memset(a, 0, 10 * sizeof(int));
    assert(reject(a, sizeof(int), 10, isZero) == 0);  // full reject
    assert(select(a, sizeof(int), 10, isZero) == 10); // full select
    for(int i = 0; i < 10; ++i) {
        assert(a[i] == 0);
    }

    a[9] = 1;
    assert(select(a, sizeof(int), 10, isZero) == 9); // all but last
    assert(reject(a, sizeof(int), 10, isZero) == 1); // none but last
    assert(a[0] == 1);
    // 1 @ index: 0, 9
    assert(reject(a, sizeof(int), 10, isZero) == 2); // first and last
    assert(a[0] == 1);
    assert(a[1] == 1);
    // 1 @ index: 0, 1, 9
    assert(select(a, sizeof(int), 10, isZero) == 7); // one large mid section
    for(int i = 0; i < 7; ++i) {
        assert(a[i] == 0);
    }
    a[1] = 1;
    a[8] = 1;
    // 1 @ index: 1, 8, 9
    assert(reject(a, sizeof(int), 10, isZero) == 3); // second and last two
    for(int i = 0; i < 3; ++i) {
        assert(a[i] == 1);
    }
    a[5] = 1;
    a[6] = 1;
    // 1 @ index: 0, 1, 2, 5, 6, 8, 9
    assert(select(a, sizeof(int), 10, isZero) == 3); // scattered, not starting
    for(int i = 0; i < 3; ++i) {                     // at array onset
        assert(a[i] == 0);
    }
    // 1 @ index: 5, 6, 8, 9
    assert(select(a, sizeof(int), 10, isZero) == 6); // scattered, starting
    for(int i = 0; i < 6; ++i) {                     // at array onset
        assert(a[i] == 0);
    }


    /* DELETE AT INDEX */

    for(int i = 0; i < 10; ++i) {
        a[i] = i;
    }

    assert(!deleteAtIndex(a, sizeof(int), 10, 10)); // out of bounds
    for(int i = 0; i < 10; ++i) {
        assert(a[i] == i);
    }
    assert(deleteAtIndex(a, sizeof(int), 10, 9));   // delete last
    for(int i = 0; i < 9; ++i) {
        assert(a[i] == i);
    }
    assert(shift(a, sizeof(int), 9));               // delete first
    for(int i = 0; i < 8; ++i) {
        assert(a[i] == i+1);
    }
    assert(deleteAtIndex(a, sizeof(int), 8, 3));    // delete in middle
    for(int i = 0; i < 3; ++i) {
        assert(a[i] == i+1);
    }
    for(int i = 3; i < 7; ++i) {
        assert(a[i] == i+2);
    }


    /* DELETE ON MATCH */

    /* FIRST MATCH */

    for(int i = 0; i < 10; ++i) {   // fill with 1...10
        a[i] = i+1;
    }
    assert(!deleteFirstMatch(a, sizeof(int), 10, isZero)); // no match
    for(int i = 0; i < 10; ++i) {
        assert(a[i] == i+1);
    }

    a[9] = 0;
    assert(deleteFirstMatch(a, sizeof(int), 10, isZero));  // last matches
    for(int i = 0; i < 9; ++i) {
        assert(a[i] == i+1);
    }

    a[0] = 0;
    assert(deleteFirstMatch(a, sizeof(int), 9, isZero));   // first matches
    for(int i = 0; i < 8; ++i) {
        assert(a[i] == i+2);
    }

    a[3] = 0;
    assert(deleteFirstMatch(a, sizeof(int), 8, isZero));   // match in middle
    for(int i = 0; i < 3; ++i) {
        assert(a[i] == i+2);
    }
    for(int i = 3; i < 7; ++i) {
        assert(a[i] == i+3);
    }

    a[0] = 1;
    a[1] = 0;
    a[2] = 1;
    a[3] = 0;
    a[4] = 1;
    // 2 matches; only first deleted
    assert(deleteFirstMatch(a, sizeof(int), 5, isZero));
    assert(a[0] == 1);
    assert(a[1] == 1);
    assert(a[2] == 0);
    assert(a[3] == 1);


    /* LAST MATCH */

    for(int i = 0; i < 10; ++i) {   // fill with 1...10
        a[i] = i+1;
    }
    assert(!deleteLastMatch(a, sizeof(int), 10, isZero)); // no match
    for(int i = 0; i < 10; ++i) {
        assert(a[i] == i+1);
    }

    a[9] = 0;
    assert(deleteLastMatch(a, sizeof(int), 10, isZero));  // last matches
    for(int i = 0; i < 9; ++i) {
        assert(a[i] == i+1);
    }

    a[0] = 0;
    assert(deleteLastMatch(a, sizeof(int), 9, isZero));   // first matches
    for(int i = 0; i < 8; ++i) {
        assert(a[i] == i+2);
    }

    a[3] = 0;
    assert(deleteLastMatch(a, sizeof(int), 8, isZero));   // match in middle
    for(int i = 0; i < 3; ++i) {
        assert(a[i] == i+2);
    }
    for(int i = 3; i < 7; ++i) {
        assert(a[i] == i+3);
    }

    a[0] = 1;
    a[1] = 0;
    a[2] = 1;
    a[3] = 0;
    a[4] = 1;
    // 2 matches; only last deleted
    assert(deleteLastMatch(a, sizeof(int), 5, isZero));
    assert(a[0] == 1);
    assert(a[1] == 0);
    assert(a[2] == 1);
    assert(a[3] == 1);

	exit(EXIT_SUCCESS);
}
