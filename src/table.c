#include "table.h"

table *table_make_from_cols(size_t n_cols, line *first_col, ...)
{
    if (n_cols == 0 || first_col == NULL) return NULL;
    line **arr = malloc(sizeof(line*) * n_cols);
    if (arr == NULL) return NULL;
    arr[0] = first_col;
    va_list factor;
    va_start(factor, n_cols - 1);
    for (size_t i = 1; i < n_cols; i++)
    {
        arr[i] = va_arg(factor, line *);
        if (!arr[i]) {
            free(arr);
            return NULL;
        }
    }
    va_end(factor);
    return table_make_from_cols_arr(n_cols, arr);
}

table *table_make_from_cols_arr(size_t n_cols, line **cols)
{
    if (cols == NULL || n_cols == 0)
        return NULL;
    table *res = malloc(sizeof(table));
    if (res == NULL)
    {
        free(res);
        return NULL;
    }
    res->n_cols = n_cols;
    res->cols = cols;
    res->n_rows = res->cols[0]->len;
    // Check if all cols have same lengths
    for (size_t i = 1; i < n_cols; i++)
    {
        if (res->cols[i]->len != res->n_rows)
        {
            free(res);
            return NULL;
        }
    }
    return res;
}

table *table_make_from_rows(size_t n_rows, line *first_row, ...) {
    if (n_rows == 0 || first_row == NULL)
        return NULL;
    line **arr = malloc(sizeof(line *) * n_rows);
    if (arr == NULL)
        return NULL;
    arr[0] = first_row;
    va_list factor;
    va_start(factor, n_rows - 1);
    for (size_t i = 1; i < n_rows; i++)
    {
        arr[i] = va_arg(factor, line *);
        if (!arr[i])
        {
            free(arr);
            return NULL;
        }
    }
    va_end(factor);
    return table_make_from_rows_arr(n_rows, arr);
}

table *table_make_from_rows_arr(size_t n_rows, line **rows) {
    if (rows == NULL || n_rows == 0)
        return NULL;
    table *res = malloc(sizeof(table));
    if (res == NULL)
    {
        free(res);
        return NULL;
    }
    res->n_rows = n_rows;
    res->n_cols = rows[0]->len;
    // Check lengths
    for (size_t i = 0; i < n_rows; i++) {
        if (rows[i]->len != res->n_cols) {
            free(res);
            return NULL;
        }
    }
    // Make columns
    res->cols = malloc(sizeof(line *) * res->n_cols);
    double *col_data = malloc(sizeof(double) * res->n_rows);
    if (res->cols == NULL || col_data == NULL) {
        free(res);
        return NULL;
    }
    // copy data
    for (size_t i = 0; i < res->n_cols; i++) {
        for (size_t j = 0; j < n_rows; j++) {
            col_data[j] = rows[j]->data[i];
        }
        res->cols[i] = line_make_eq(n_rows, 0.);
        if (res->cols[i] == NULL) {
            for (size_t j = i; j >= 0; j--) {
                free_line(res->cols[j]);
            }
            free(res->cols);
            free(col_data);
            free(res);
            return NULL;
        }
        for (size_t j = 0; j < n_rows; j++) {
            res->cols[i]->data[j] = col_data[j];
        }
    }
    free(col_data);
    return res;
}

table *table_make_empty(size_t n_cols) {
    table *res = malloc(sizeof(table));
    if (res == NULL)
    {
        free(res);
        return NULL;
    }
    res->n_cols = n_cols;
    res->n_rows = 0;
    res->cols = malloc(sizeof(line *) * n_cols);
    if (res->cols == NULL)
    {
        free(res);
        return NULL;
    }
    for (size_t i = 0; i < n_cols; i++) {
        res->cols[i] = line_make(0, 0.);
        if (res->cols[i] == NULL)
        {
            for (size_t j = i; j >= 0; j--)
            {
                free_line(res->cols[j]);
            }
            free(res->cols);
            free(res);
            return NULL;
        }
    }
    return res;
}

table *table_make_eq(size_t n_cols, size_t n_rows, double val) {
    table *res = malloc(sizeof(table));
    if (res == NULL)
    {
        free(res);
        return NULL;
    }
    res->n_cols = n_cols;
    res->n_rows = n_rows;
    res->cols = malloc(sizeof(line *) * n_cols);
    if (res->cols == NULL)
    {
        free(res);
        return NULL;
    }
    for (size_t i = 0; i < n_cols; i++)
    {
        res->cols[i] = line_make_eq(n_rows, val);
        if (res->cols[i] == NULL)
        {
            for (size_t j = i; j >= 0; j--)
            {
                free_line(res->cols[j]);
            }
            free(res->cols);
            free(res);
            return NULL;
        }
    }
    return res;
}

short check_table(table *t, short check_null, short check_data_null, short check_r_gt0, short check_c_gt1, short check_lines) {
    if (check_null && t == NULL) {
        return 1;
    }
    if (check_data_null && t->cols == NULL) {
        return 2;
    }
    if (check_r_gt0 && t->n_rows < 0) {
        return 3;
    }
    if (check_c_gt1 && t->n_cols < 1) {
        return 4;
    }
    if (check_lines) {
        for (size_t i = 0; i < t->n_cols; i++) {
            if (!t->cols[i]) return 5;
        }
    }
    return 0;
}

void free_table(table *t) {
    short c = check_table(t, 1, 1, 0, 0, 0);
    if (c == 1) return;
    if (c == 2) {
        free(t);
        return;
    }
    for (size_t i = 0; i < t->n_cols; i++) {
        free_line(t->cols[i]);
    }
    free(t->cols);
    free(t);
}

table *table_copy(table *t) {
    if (check_table(t, 1, 1, 0, 0, 1)) return NULL;
    table *res = table_make_eq(t->n_cols, t->n_rows, 0.);
    if (!res) return NULL;
    for (size_t i = 0; i < t->n_cols; i++) {
        for (size_t j = 0; j < t->n_rows; j++) {
            res->cols[i]->data[j] = t->cols[i]->data[j];
        }
    }
    return res;
}

short table_rowadd_toend(table *t, line *row) {
    if (check_table(t, 1, 1, 0, 0, 1) || !row || !row->data || row->len != t->n_cols)
        return 1;
    t->n_rows += 1;
    for (size_t i = 0; i < t->n_cols; i++) {
        double src[1] = {row->data[i]};
        line_toend_src(t->cols[i], src, 1);
    }
    return 0;
}

short table_coladd(table *t, line *col, size_t ind) {
    if (check_table(t, 1, 1, 0, 0, 1) || ind > t->n_cols || !col || !col->data || col->len != t->n_rows)
        return 1;
    t->n_cols += 1;
    t->cols = realloc(t->cols, sizeof(line *) * t->n_cols);
    if (!t->cols) return 1;
    for (size_t i = t->n_cols - 1; i > ind; i++) {
        t->cols[i] = t->cols[i-1];
    }
    t->cols[ind] = col;
    return 0;
}

short table_rowsadd_toend(table *t, line **rows, size_t n) {
    if (check_table(t, 1, 1, 0, 0, 1) || !rows)
        return 1;
    if (n == 0) 
        return 0;
    for (size_t i = 0; i < n; i++)
    {
        if (!rows[i])
            return 1;
    }
    for (size_t i = 0; i < n; i++)
    {
        short res = table_rowadd_toend(t, rows[i]);
        if (res) 
            return 1; // Table will be corrupted
    }
}

short table_colsadd(table *t, line **cols, size_t *ind, size_t n) {
    if (check_table(t, 1, 1, 0, 0, 1) || !cols || !ind)
        return 1;
    if (n == 0)
        return 0;
    for (size_t i = 0; i < n; i++)
    {
        if (!cols[i])
            return 1;
    }
    for (size_t i = 0; i < n; i++)
    {
        short res = table_rowadd(t, cols[i], ind[i]);
        if (res)
            return 1; // Table will be corrupted
    }
}

short table_rowrm(table *t, size_t ind) {

}

short table_colrm(table *t, size_t ind) {

}

short table_rowsrm(table *t, size_t *ind, size_t n) {

}

short table_colsrm(table *t, size_t *ind, size_t n) {

}

short table_rowsrm_ind(table *t, size_t ind, size_t start, size_t end) {

}

short table_colsrm_ind(table *t, size_t ind, size_t start, size_t end) {

}

short table_compare(table *t1, table *t2) {
    if (check_table(t1, 1, 1, 0, 0, 1) || check_table(t2, 1, 1, 0, 0, 1) || t1->n_cols != t2-> n_cols || t1->n_rows != t2->n_rows)
        return 1;
    for (size_t i = 0; i < t1-> n_cols; i++) {
        for (size_t j = 0; j < t1->n_rows; j++) {
            if (t1->cols[i]->data[j] != t2->cols[i]->data[j]) {
                return 1;
            }
        }
    }
    return 0;
}

table *table_concat_v(table *t1, table *t2) {

}

table *table_concat_h(table *t1, table *t2) {

}

void table_map(table *t, double (*op)(double)) {

}

long double table_reduce(table *t, long double (*op)(long double, double)) {

}

double table_reduce_d(table *t, double (*op)(double, double)) {

}

int **table_filter(table *t, int (*filter)(double)) {

}

line *table_row_copy(table *t, size_t ind) {
    if (check_table(t, 1, 1, 0, 0, 1) || ind >= t->n_rows)
        return NULL;
    line *res = line_make(t->n_cols, 0.);
    if (!res) return NULL;
    for (size_t i = 0; i < t->n_cols; i++) {
        res->data[i] = t->cols[i]->data[ind];
    }
    return res;
}

line *table_col_copy(table *t, size_t ind) {
    if (check_table(t, 1, 1, 0, 0, 1) || ind >= t->n_cols) return NULL;
    return line_copy(t->cols[ind]);
}

table *table_tr(table *t) {

}

short table_tr_nocopy(table *t) {

}

table *table_slice(table *t, size_t r_from, size_t r_to, int r_step, size_t c_from, size_t c_to, int c_step) {

}

void table_print(table *t) {
    if (check_table(t, 1, 1, 0, 0, 1)) {
        puts("Invalid table in table_print");
        return;
    }
    printf(":start (%d x %d):\n", t->n_cols, t->n_rows);
    for (size_t i = 0; i < t->n_rows; i++) {
        printf("|%d:\t", i);
        for (size_t j = 0; j < t->n_cols; j++) {
            printf("%lf\t", t->cols[j]->data[i]);
        }
        puts("|");
    }
    puts(":end:");
}

int *filter_cols(table *t, int (*filter)(line *)) {

}

int *filter_rows(table *t, int (*filter)(line *)) {

}

table *select_cols(table *t, int (*filter)(line *)) {

}

table *select_rows(table *t, int (*filter)(line *)) {

}