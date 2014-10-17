#include "mylib.h"


/*changes all elements in array according to given function*/
void *map(void * const array, const size_t el_size,
			const size_t num_els, void (*const func)(void *a))
{
	for(size_t i = 0; i < num_els; i++)
		func((char*)array + i * el_size);

	return array;
}


/*computes a value from base element and all array elements*/
void *reduce(const void * const array, void * const base_el,
			const size_t el_size, const size_t num_els,
			void (*const func)(void *el, void *a))
{
	for(size_t i = 0; i < num_els; i++)
		func(base_el, (char*)array + i * el_size);

	return base_el;
}


/*return index of first appearance of element in array,
  -1 if element not in array*/
int indexOf(const void * const array, const void * const el_to_find,
				const size_t el_size, const size_t num_els)
{
	bool el_found;
	char *p = (char*)array;

	for(int i = 0; (size_t)i < num_els; i++, p += el_size) {	//for each el
		el_found = true;
		for(size_t el_i = 0; el_i < el_size; el_i++) {			//check each
			if(*(p + el_i) != *((char*)el_to_find + el_i)) {	//byte of el
				el_found = false;
				break;
			}
		}
		if(el_found) return i;
	}

	return -1;
}
