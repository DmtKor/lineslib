#include "../src/table.h"
#include "../src/dep/Unity/src/unity.h"

line null_data_line = {1, NULL};

line *line1;
line *line2;
line *line3;
line *line4;
line *line5;
line *line6;
line *line7;
line *line8;
line *line9;
line *line10;

table null_data_table = {1, 1, NULL};

table *t1;
table *t2;
table *t3;
table *t4;
table *t5;
table *t6;
table *t7;
table *t8;

double op_sq(double val) { return val * val; } 

void setUp() {
    line1 = &null_data_line;
    line2 = NULL;
    line3 = line_make(0, 0.);
    line4 = line_make(0, 0.);
    line5 = line_make(1, 0.25);
    line6 = line_make(1, 0.25);
    line7 = line_make_eq(8, 0.1);
    line8 = line_make(8, 1., 2., 3., 4., 5., 6., 7., 8.);
    line9 = line_copy(line8);
    line10 = line_copy(line9);
    line_map(line10, op_sq);

    t1 = &null_data_table;
    t2 = NULL;
    t3 = table_make_eq(0, 0, 0.1);
    t4 = table_make_eq(3, 0, 0.1);
    t5 = table_make_eq(0, 3, 0.1);
    t6 = table_make_eq(3, 3, 0.1);
    t7 = table_make_from_cols(2, line7, line8);
    t8 = table_make_from_cols(2, line9, line10);
}

void tearDown() {
    free_line(line1);
    free_line(line2);
    free_line(line3);
    free_line(line4);
    free_line(line5);
    free_line(line6);
    free_line(line7);
    free_line(line8);
    free_line(line9);
    free_line(line10);
    free_table(t1);
    free_table(t2);
    free_table(t3);
    free_table(t4);
    free_table(t5);
    free_table(t6);
    free_table(t7);
    free_table(t8);
}

void test_make_from_cols() {

}

void test_make_from_cols_arr() {}

void test_make_from_rows() {}

void test_make_from_rows_arr() {}

void test_make_empty() {}

void test_make_eq() {}

void test_check_table() {}

void test_copy() {}

void test_row_copy() {}

void test_col_copy() {}

void test_compare() {}

void test_rowadd_toend() {}

void test_coladd() {}

void test_rowsadd_toend() {}

void test_colsadd() {}

void test_rowrm() {}

void test_colrm() {}

void test_rowsrm() {}

void test_colsrm() {}

void test_rowsrm_ind() {}

void test_colsrm_ind() {}

void test_concat_v() {}

void test_concat_h() {}

void test_map() {}

void test_reduce() {}

void test_reduce_d() {}

void test_tr() {}

void test_tr_nocopy() {}

void test_slice() {}

void test_filter_r() {}

void test_filter_c() {}

void test_select_r() {}

void test_select_c() {}

void test_print() {}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_make_from_cols);
    RUN_TEST(test_make_from_cols_arr);
    RUN_TEST(test_make_from_rows);
    RUN_TEST(test_make_from_rows_arr);
    RUN_TEST(test_make_empty);
    RUN_TEST(test_make_eq);
    RUN_TEST(test_check_table);
    RUN_TEST(test_copy);
    RUN_TEST(test_row_copy);
    RUN_TEST(test_col_copy);
    RUN_TEST(test_compare);
    RUN_TEST(test_rowadd_toend);
    RUN_TEST(test_coladd);
    RUN_TEST(test_rowsadd_toend);
    RUN_TEST(test_colsadd);
    RUN_TEST(test_rowrm);
    RUN_TEST(test_colrm);
    RUN_TEST(test_rowsrm);
    RUN_TEST(test_colsrm);
    RUN_TEST(test_rowsrm_ind);
    RUN_TEST(test_colsrm_ind);
    RUN_TEST(test_concat_v);
    RUN_TEST(test_concat_h);
    RUN_TEST(test_map);
    RUN_TEST(test_reduce);
    RUN_TEST(test_reduce_d);
    RUN_TEST(test_tr);
    RUN_TEST(test_tr_nocopy);
    RUN_TEST(test_slice);
    RUN_TEST(test_filter_r);
    RUN_TEST(test_filter_c);
    RUN_TEST(test_select_r);
    RUN_TEST(test_select_c);
    RUN_TEST(test_print);
    return UNITY_END();
}