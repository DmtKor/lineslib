#include "line.h"


// STRUCTURES

/*
table: list of lines
should be created via table_make* functions
should be deleted with free_table function
should be manipulated with table_* functions

Direct access to fields:
    - n_cols - cols number (size_t)
    - n_rows - rows number (size_t)
    - cols - pointer to an actual array (line **)
*/
typedef struct
{
    size_t n_cols;
    size_t n_rows;
    line **cols;
} table;


// TABLE FUNCTIONS

/*
Make new table from column lines, pointers are copied into line **cols of table
That means, first_col and other lines passed into function should not be deleted with free_line
if you don't want to break a table

n_cols - number of columns (including first_col)

Returns pointer to table on success, NULL otherwise
*/
table *table_make_from_cols(size_t n_cols, line *first_col, ...);

/*
Make new table from column lines array, pointer is copied into line **cols of table
That means, cols elements and array itself should not be deleted with free_line,
if you don't want to break a table

n_cols - number of columns (including first_col)

Returns pointer to table on success, NULL otherwise
*/
table *table_make_from_cols_arr(size_t n_cols, line **cols);

/*
WORKS SLOWER THAN table_make_from_cols*!
Make new table from row lines
You should free() pointers afterwards (data is copied)

n_rows - number of rows (including first_row)

Returns pointer to table on success, NULL otherwise
*/
table *table_make_from_rows(size_t n_rows, line *first_row, ...);

/*
WORKS SLOWER THAN table_make_from_cols*!
Make new table from array of row lines
You should free() pointers afterwards (data is copied)

n_rows - number of rows (including first_row)

Returns pointer to table on success, NULL otherwise
*/
table *table_make_from_rows_arr(size_t n_rows, line **rows);

/*
Make new empty table

size_t n_cols - number of columns

Returns pointer to table on success, NULL otherwise
*/
table *table_make_empty(size_t n_cols);

/*
Make new table filled with same values

size_t n_cols - number of columns
double val - default value

Returns pointer to table on success, NULL otherwise
*/
table *table_make_eq(size_t n_cols, size_t n_rows, double val);

/*
Check if table is NULL | line **cols is NULL | n_rows > 0 | n_cols > 1
Internal

Returns 0 if table pass
*/
short check_table(table *t, short check_null, short check_data_null, short check_r_gt0, short check_c_gt1, short check_lines);

/*
Free table data (including table *pointer)
*/
void free_table(table *t);

/*
Make new table from existing one

Returns pointer to new table on success, NULL otherwise
*/
table *table_copy(table *t);

/*
Add new row to end
You should free row afterwards

Returns 0 on success, 1 otherwise
*/
short table_rowadd_toend(table *t, line *row);

/*
Add new col at index ind, all existing cols starting from ind will be moved to right

Returns 0 on success, 1 otherwise
*/
short table_coladd(table *t, line *col, size_t ind);

/*
Add new rows to end
You should free rows and its elements afterwards

Returns 0 on success, 1 otherwise
*/
short table_rowsadd_toend(table *t, line **rows, size_t n);

/*
Add new cols at indices ind
Cols are added starting from ind[0], every time table_coladd is called

Returns 0 on success, 1 otherwise
*/
short table_colsadd(table *t, line **cols, size_t *ind, size_t n);

/*
Remove row by index

Returns 0 on success, 1 otherwise
*/
short table_rowrm(table *t, size_t ind);

/*
Remove col by index

Returns 0 on success, 1 otherwise
*/
short table_colrm(table *t, size_t ind);

/*
Remove rows by indices

Returns 0 on success, 1 otherwise
*/
short table_rowsrm(table *t, size_t *ind, size_t n);

/*
Remove cols by indices

Returns 0 on success, 1 otherwise
*/
short table_colsrm(table *t, size_t *ind, size_t n);

/*
Remove rows by indices in [start; end]

Returns 0 on success, 1 otherwise
*/
short table_rowsrm_ind(table *t, size_t ind, size_t start, size_t end);

/*
Remove cols by indices in [start; end]

Returns 0 on success, 1 otherwise
*/
short table_colsrm_ind(table *t, size_t ind, size_t start, size_t end);

/*
Compare two tables

Returns 0 on equal, 1 on not equal
*/
short table_compare(table *t1, table *t2);

/*
Concatenate two tables vertically
Creates new table

Returns pointer to table on success, NULL otherwise
*/
table *table_concat_v(table *t1, table *t2);

/*
Concatenate two tables horizontally
Creates new table

Returns pointer to table on success, NULL otherwise
*/
table *table_concat_h(table *t1, table *t2);

/*
Change every table item to op(item)
*/
void table_map(table *t, double (*op)(double));

/*
Reduce table to a single long double value (table continues to exist)
On error returns 0
*/
long double table_reduce(table *t, long double (*op)(long double, double));

/*
Reduce table to a single double value (table continues to exist)
On error returns 0
*/
double table_reduce_d(table *t, double (*op)(double, double));

/*
Returns 2D array (dynamically allocated) of filter(item) for every table item, NULL on error
*/
int **table_filter(table *t, int (*filter)(double));

/*
Copy row from table into new line

Returns pointer to new line, NULL on error
*/
line *table_row_copy(table *t, size_t ind);

/*
Copy col from table into new line

Returns pointer to new line, NULL on error
*/
line *table_col_copy(table *t, size_t ind);

/*
Make new table where cols are existing tables rows

Returns pointer to table on success, NULL otherwise
*/
table *table_tr(table *t);

/*
Change table: new cols are this table's rows

Returns pointer to table on success, NULL otherwise
*/
short table_tr_nocopy(table *t);

/*
Get slice from table (including r_to, c_to element)

Returns pointer to the new table on success, NULL otherwise
*/
table *table_slice(table *t, size_t r_from, size_t r_to, int r_step, size_t c_from, size_t c_to, int c_step);

/*
Print table
*/
void table_print(table *t);

/*
Make (dyn. all.) table of filter(col) values for each col

Returns int * pointer, NULL on error
*/
int *filter_cols(table *t, int (*filter)(line *));

/*
Make (dyn. all.) table of filter(row) values for each row

Returns int * pointer, NULL on error
*/
int *filter_rows(table *t, int (*filter)(line *));

/*
Make new table from columns with non-zero filter(col) values

Returns pointer to the new table on success, NULL otherwise
*/
table *select_cols(table *t, int (*filter)(line *));

/*
Make new table from rows with non-zero filter(row) values

Returns pointer to the new table on success, NULL otherwise
*/
table *select_rows(table *t, int (*filter)(line *));