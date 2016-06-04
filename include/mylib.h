#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <stdlib.h>
#include <stdbool.h>



/*Remove all characters until newline (inclusive) from given input stream.
  Usage only advised for stdin. Should only be called when it is certain
  that a newline is still present in the input buffer*/
#define flushln(instream) while(fgetc(instream) != '\n')


/*Convenience macros for using the map function with specific data types*/
#define mapInt(array, num, func)	map(array, sizeof(int), num, func)
#define mapDouble(array, num, func)	map(array, sizeof(double), num, func)


/*Convenience macros for using the reduce function with specific data types*/
#define reduceInt(array, base, num_els, func)\
	reduce(array, base, sizeof(int), num_els, func)
#define reduceDouble(array, base, num_els, func)\
	reduce(array, base, sizeof(double), num_els, func)


/*Convenience macros for using the indexOf function with specific data types*/
#define indexOfInt(array, el_to_find, num_els)\
	indexOf(array, el_to_find, sizeof(int), num_els)
#define indexOfDouble(array, el_to_find, num_els)\
	indexOf(array, el_to_find, sizeof(double), num_els)


/*Returns true if the element is contained in array, false otherwise.
  Implemented by checking whether the indexOf function finds the element*/
#define contains(array, el_to_find, el_size, num_els)\
	(indexOf(array, el_to_find, el_size, num_els) >= 0)


/*Convenience macros for using the contains function with specific data types*/
#define containsInt(array, el_to_find, num_els)\
	(indexOf(array, el_to_find, sizeof(int), num_els) >= 0)
#define containsDouble(array, el_to_find, num_els)\
	(indexOf(array, el_to_find, sizeof(double), num_els) >= 0)


/*Changes all elements of array according to given function*/
void *map(void *const array, const size_t el_size,
			const size_t num_els, void (*const func)(void *a));


/*Computes a new value using the given base value by iterating through
  the given array. In each iteration, the value is updated by a computation
  made by the given function, which takes the current value and the value
  of the current array index as arguments*/
void *reduce(const void *const array, void *const base_el,
			const size_t el_size, const size_t num_els,
			void (*const func)(void *el, void *a));


/*Returns index of the first occurence of the element in the array,
  or -1 if not found*/
int indexOf(const void *const array, const void *const el_to_find,
				const size_t el_size, const size_t num_els);

#endif
