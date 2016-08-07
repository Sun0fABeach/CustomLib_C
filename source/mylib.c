#include <string.h>
#include "mylib.h"


void *map(void *const array, const size_t el_size,
			const size_t num_els, void (*const func)(void *a))
{
	for(size_t i = 0; i < num_els; i++)
		func((char*)array + i * el_size);

	return array;
}


void *reduce(const void *const array, void *const base_el,
			const size_t el_size, const size_t num_els,
			void (*const func)(void *el, void *a))
{
	for(size_t i = 0; i < num_els; i++)
		func(base_el, (char*)array + i * el_size);

	return base_el;
}


int indexOf(const void *const array, const void *const el_to_find,
				const size_t el_size, const size_t num_els)
{
	const char *p = array;

	for(int i = 0; (size_t)i < num_els; ++i, p += el_size) {	//for each el
		bool el_found = true;
		for(size_t el_i = 0; el_i < el_size; ++el_i) {			//check each
			if(*(p + el_i) != *((char*)el_to_find + el_i)) {	//byte of el
				el_found = false;
				break;
			}
		}
		if(el_found) return i;
	}

	return -1;
}


size_t sortOut(void *const array, const size_t el_size, const size_t num_els,
        bool (*const matchTest)(const void *el), const bool keep_on_match)
{
    const char *p = array;
    char *move_pos = NULL;
    size_t new_size = 0;
    size_t i;

    for(i = 0; i < num_els; ++i) {  // find first non-match
        if(matchTest(p) != keep_on_match) {
            move_pos = (char *)p;
            break;
        }
        ++new_size;
        p += el_size;
    }

    if(!move_pos)
        return num_els;  // no non-match found: keep all

    size_t move_num = 0;

    while(++i < num_els) {
        p += el_size;

        if(matchTest(p) == keep_on_match) {
            ++move_num;
        } else if(move_num > 0) {
            const size_t bytes_to_move = move_num * el_size;
            memmove(move_pos, p - bytes_to_move, bytes_to_move);
            move_pos += bytes_to_move;
            new_size += move_num;
            move_num = 0;
        }
    }

    if(move_num > 0) { // past array end and pending bytes to move?
        const size_t bytes_to_move = move_num * el_size;
        memmove(move_pos, p - bytes_to_move + el_size, bytes_to_move);
        new_size += move_num;
    }

    return new_size;
}


bool deleteAtIndex(void *const array, const size_t el_size,
        const size_t num_els, const size_t index)
{
    if(index >= num_els)
        return false;

    char *const delete_pos = (char *)array + index * el_size;

    memmove(delete_pos, delete_pos + el_size, (num_els - index - 1) * el_size);

    return true;
}
