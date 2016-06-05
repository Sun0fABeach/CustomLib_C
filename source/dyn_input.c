#include <stdlib.h>
#include <stdbool.h>
#include "dyn_input.h"


/******** Dynamic char buffer globals ********/

#define STARTING_CAP 50

static void freeBuf();

static char *buf = NULL;
static size_t cap = STARTING_CAP;


/******** Dynamic string array globals ********/

#define STARTING_STR_MAX 10
#define STARTING_STR_LENGTH 50

static bool getInput(FILE *instream, size_t i, size_t length);
static void freeStrings();

static char **strings = NULL;	//array that holds the strings
static size_t nstrings = 0;		//current number of allocated strings
static size_t nstrings_max = STARTING_STR_MAX;


/******** Dynamic char buffer functions ********/

char *fBufRead(FILE *const instream)
{
	if(!buf) {					//first call: init buffer
		if((buf = malloc(STARTING_CAP * sizeof(char))) == NULL)
			return NULL;		//abort if buffer can't be allocated
		else
			atexit(freeBuf);
	}

	int c;
	size_t i = 0;

	while((c = getc(instream)) != '\n' && c != EOF) {
		buf[i] = c;

		if(++i == cap) {		//buffer needs doubling:
			cap *= 2;
            char *doubledBuf = realloc(buf, cap * sizeof(char));
			if(doubledBuf == NULL)
				return NULL;	//abort if resizing failed
			else
				buf = doubledBuf;
		}
	}

	buf[i] = '\0';		//overwrites newline, if present
	return buf;
}


static void freeBuf()
{
	free(buf);
}



/******** Dynamic string array functions ********/

char *fReadLine(FILE *const instream)
{
	if(strings == NULL) {
		if((strings = calloc(STARTING_STR_MAX, sizeof(char *)))) //init all NULL
			atexit(freeStrings);
		else
			return NULL;
	}

	if(!getInput(instream, 0, STARTING_STR_LENGTH))
		return NULL;

	if(++nstrings == nstrings_max) {
		nstrings_max *= 2;
		if(!(strings = realloc(strings, nstrings_max * sizeof(char*))))
			return NULL;
	}

	return strings[nstrings - 1];
}

/*
  handles string reading, returns false when reallocation error occurred
  true otherwise
*/
static bool getInput(FILE *const instream, size_t i, const size_t length)
{
	if(!(strings[nstrings] = realloc(strings[nstrings], length * sizeof(char))))
		return false;	//does malloc if strings[nstrings] is NULL

	while(true) {
        char c = getc(instream);
		if(c == '\n' || c == EOF) {
			strings[nstrings][i] = '\0';    //overwrites newline
			return true;
		}
		strings[nstrings][i] = c;

		if(++i == length)
			return getInput(instream, i, length * 2);
	}
}


size_t num_strings()
{
    return nstrings;
}


static void freeStrings()
{
	clearStrings();
	free(strings);
}

size_t clearStrings()
{
	size_t i = 0;
	for(i = 0; i < nstrings; ++i) {
		free(strings[i]);
		strings[i] = NULL;
	}
	nstrings = 0;
	return i;
}
