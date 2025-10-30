#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


// STRUCTURES

/* 
line: main lib data structure representing vector
should be created via line_make_* functions
should be deleted with free_line function
should be manipulated with line_* functions

Direct access to fields:
    - len - vector length (size_t)
    - data - pointer to an actual array (double *)
*/
typedef struct
{
    size_t len; 
    double *data; 
} line;


// LINE FUNCTIONS

/*
copies line to the new one (including data)
when l or l->data is NULL, returns NULL
*/
line *line_copy(line *l);

/*
make line with 'len' (size_t) values
all values types should be double

Returns pointer to line or NULL if fails
*/
line *line_make(size_t len, ...);

/*
make line with 'len' (size_t) values
'value' (double) parameter is a default value for all elements

Returns pointer to line or NULL if fails
*/
line *line_make_eq(size_t len, double value);

/*
make line with 'len' (size_t) values
src (double *) array is where this function gets values from, it should has same or greater length
this function doesn't call free(src)

Returns pointer to line or NULL if fails
*/
line *line_make_src(size_t len, double *src);

/*
compare lines. If equal (lengths and values)

Returns: 
- 0 if lines have equal lengths and values
- 1 if first line length is bigger 
- 2 if second line length is bigger
- -1 if lengths are equal, but values aren't
- -2 if one or both lines (or their data) is NULL pointer
*/
short line_compare(line *l1, line *l2);

/*
add values from src (double *) array of length 'src_len' (size_t) to the end of l (line *) array
when fails, doesn't change anything. If realloc call inside fails, your data will be lost.
*/
void line_toend_src(line *l, size_t src_len, double *src);

/*
concatenates lines l1 and l2 (line *) into new line
does not delete old ones

Returns pointer to line or NULL if fails, l1 and l2 do not change
*/
line *line_concat(line *l1, line *l2);

/*
replaces each value in line with op result on this value
when fails doesn't change anything
*/
void line_map(line *l, double (*op)(double));

/*
returns mask of line by applying filter function to each value
when fails doesn't change anything, returns NULL
result is dynamically allocated, so you should call free() when it's no longer needed
if len = 0, returns NULL
*/
int *line_filter(line *l, int (*filter)(double));

/*
reduces line values to a single one (long double)
for example, with op being ... { return val1 + val2 } you'll get sum of all elements
when l is empty, returns 0
when l has one value, returns this value without changing it
*/
long double line_reduce(line *l, long double (*op)(long double, double));

/*
reduces line values to a single one (double)
for example, with op being ... { return val1 + val2 } you'll get sum of all elements
when l is empty, returns 0
when l has one value, returns this value without changing it
*/
double line_reduce_d(line *l, double (*op)(double, double));

/*
internal function, counts non-zero elements in int array
*/
size_t mask_count(size_t len, int *mask);

/*
selects all elements that have non-zero mask values and returns resulting line
gets mask values using filter function
old line does not get deleted
*/
line *line_select(line *l, int (*filter)(double));

/*
get slice from lines, works like [from:to:step] in python
i.e. it starts selecting elements from index (i) 'from',
than i = from + step, i = from + step * 2, ... until i == to becomes true.
it is important to know that 'to' point IS included into final line.
for example, if you want to get a slice with all elements: from = 0, to = len-1, step = 1
if you want to reverse line, you could change it to: from = len-1, to = 0, step = -1
in case of incorrect arguments returns empty line
this function doesn't delete old line
*/
line *line_slice(line *l, size_t from, size_t to, int step);

/*
applies op to each corresponding pairs of elements in both lines an returns resulting line
l1->len should be equal to l2->len
does not delete old lines
*/
line *line_combine(line *l1, line *l2, double (*op)(double, double));

/*
prints line or error message if l or l->data is a NULL pointer
this function doesn't print newlines in case user don't need them
*/
void line_print(line *l);

/*
delete line l
*/
void free_line(line *l);


// FILTER FUNCTIONS

/* todo */


// REDUCE OPERATORS

/* todo */


// COMBINE OPERATORS

/* todo */


// MAP FUNCTIONS

/* todo */