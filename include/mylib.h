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


/*Convenience macros for using deleteAtIndex with specific data types*/
#define deleteIntAtIndex(array, num_els, index) \
    deleteAtIndex(array, sizeof(int), num_els, index)
#define deleteDoubleAtIndex(array, num_els, index) \
    deleteAtIndex(array, sizeof(double), num_els, index)


/*Deletes first element of given array at given index by moving all the
  following elements one index backwards. Returns true if the element has been
  deleted, or false if the array size is 0.
 */
#define shift(array, el_size, num_els) \
    deleteAtIndex(array, el_size, num_els, 0)


/*Convenience macros for using shift with specific data types*/
#define shiftInt(array, num_els) \
    shift(array, sizeof(int), num_els)
#define shiftDouble(array, num_els) \
    shift(array, sizeof(double), num_els)


/*Deletes all elements of the given array for which the given callback reports
  no match. Returns the new size of the array.*/
#define select(array, el_size, num_els, match_test)\
    (sortOut(array, el_size, num_els, match_test, true))


/*Deletes all elements of the given array for which the given callback reports
  a match. Returns the new size of the array.*/
#define reject(array, el_size, num_els, match_test)\
    (sortOut(array, el_size, num_els, match_test, false))


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


/*Deletes element of given array at given index by moving all the following
  elements one index backwards. Returns true if the element has been deleted,
  or false if the given index surpassed the array bounds.*/
bool deleteAtIndex(void *const array, const size_t el_size,
        const size_t num_els, const size_t index);


/*Deletes first element of given array for which the given test function
  returns true by moving all the following elements one index backwards.
  Returns true if the element has been deleted, or false if the given index
  surpassed the array bounds.*/
bool deleteFirstMatch(void *const array, const size_t el_size,
        const size_t num_els, bool (*const test)(const void *el));


/*Deletes last element of given array for which the given test function
  returns true by moving all the following elements one index backwards.
  Returns true if the element has been deleted, or false if the given index
  surpassed the array bounds.*/
bool deleteLastMatch(void *const array, const size_t el_size,
        const size_t num_els, bool (*const test)(const void *el));


/*Tests if the given test function returns true for all elements of the given
  array. Returns true if it does and false otherwise.*/
bool allMatch(void *const array, const size_t el_size,
        const size_t num_els, bool (*const test)(const void *el));


/*Deletes elements of an array and rearranges it so that all kept elements
  form a continuous sequence starting at the beginning of the array. A callback
  has to be passed which will perform the task of checking whether an element
  of the array matches. If a matching element has to be kept or deleted can be
  determined by the value of keep_on_match. Returns the number of kept elements
  which is also the new logical size of the array (physical size is unchanged).
 */
size_t sortOut(void *const array, const size_t el_size, const size_t num_els,
        bool (*const match_test)(const void *el), const bool keep_on_match);

#endif
