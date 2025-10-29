#include "../src/line.h"
#include "../src/dep/Unity/src/unity.h"


// in most functions I didn't use len argument greater than actual values count
// in this case probably user will get segfault or random garbage 
// I think there's no need to do something with that (and I probably couldn't)


void setUp() {}

void tearDown() {}


void test_make() 
{
    line *test0 = line_make(0);
    line *test1 = line_make(3, 1, 2, 3);
    line *test2 = line_make(3, 1.15, 0.25, 3.45);
    double src[3] = {1.23, 2, 3.45}; // Should take only first two
    line *test3 = line_make_src(2, src);
    line *test4 = line_make_eq(0, 0.);
    line *test5 = line_make_eq(5, 0);
    line *test6 = line_make_eq(7, 1.23);
    line *test7 = line_make(3, 1.15, 0.25, 3.45);

    TEST_ASSERT_NOT_NULL(test0);
    TEST_ASSERT_NOT_NULL(test1);
    TEST_ASSERT_NOT_NULL(test2);
    TEST_ASSERT_NOT_NULL(test3);
    TEST_ASSERT_NOT_NULL(test4);
    TEST_ASSERT_NOT_NULL(test5);
    TEST_ASSERT_NOT_NULL(test6);
    TEST_ASSERT_NOT_NULL(test7);

    TEST_ASSERT_EQUAL(0, test0->len);
    TEST_ASSERT_EQUAL(3, test1->len);
    TEST_ASSERT_EQUAL(3, test2->len);
    TEST_ASSERT_EQUAL(2, test3->len);
    TEST_ASSERT_EQUAL(0, test4->len);
    TEST_ASSERT_EQUAL(5, test5->len);
    TEST_ASSERT_EQUAL(7, test6->len);
    TEST_ASSERT_EQUAL(3, test7->len);

    free_line(test0);
    free_line(test1);
    free_line(test2);
    free_line(test3);
    free_line(test4);
    free_line(test5);
    free_line(test6);
    free_line(test7);
}


void test_compare() 
{
    line *test0 = line_make(0);
    line *test1 = line_make_eq(0, 0.);
    line *test2 = line_make(3, 1, 2, 3);
    line *test3 = line_make(3, 1.15, 0.25, 3.45);
    line *test4 = line_make(3, 1.15, 0.25, 3.45);
    line test5 = {1, NULL};

    TEST_ASSERT_EQUAL(0, line_compare(test0, test0));
    TEST_ASSERT_EQUAL(0, line_compare(test0, test1));
    TEST_ASSERT_EQUAL(0, line_compare(test1, test0));
    TEST_ASSERT_EQUAL(2, line_compare(test0, test2));
    TEST_ASSERT_EQUAL(1, line_compare(test2, test0));
    TEST_ASSERT_EQUAL(-1, line_compare(test2, test3));
    TEST_ASSERT_EQUAL(0, line_compare(test3, test4));
    TEST_ASSERT_EQUAL(-2, line_compare(test3, NULL));
    TEST_ASSERT_EQUAL(-2, line_compare(NULL, NULL));
    TEST_ASSERT_EQUAL(-2, line_compare(NULL, test3));
    TEST_ASSERT_EQUAL(-2, line_compare(test3, &test5));

    free_line(test0);
    free_line(test1);
    free_line(test2);
    free_line(test3);
    free_line(test4);
}


void test_toend()
{
    line ltest3 = {1, NULL};

    line *test00 = line_make_eq(0, 0.);
    line *test01 = line_make(3, 1., 2., 3.);
    line *test02 = NULL;
    line *test03 = &ltest3;
    line *test10 = line_make_eq(0, 0.);
    line *test11 = line_make(3, 1., 2., 3.);
    line *test12 = NULL;
    line *test13 = &ltest3;
    line *test20 = line_make_eq(0, 0.);
    line *test21 = line_make(3, 1., 2., 3.);
    line *test22 = NULL;
    line *test23 = &ltest3;

    double *src1 = NULL;
    double *src2 = NULL; 
    double src3[3] = {0., 1., 2.};

    line *actual00 = line_make(0, 0);
    line *actual01 = line_make(3, 1., 2., 3.);
    line *actual02 = NULL;
    line *actual03 = &ltest3;
    line *actual10 = line_make(0, 0);
    line *actual11 = line_make(3, 1., 2., 3.);
    line *actual12 = NULL;
    line *actual13 = &ltest3;
    line *actual20 = line_make(3, 0., 1., 2.);
    line *actual21 = line_make(6, 1., 2., 3., 0., 1., 2.);
    line *actual22 = NULL;
    line *actual23 = &ltest3;

    line_toend_src(test00, 0, src1); // shouldn't change
    line_toend_src(test01, 1, src1); // shouldn't change
    line_toend_src(test02, 2, src1); // shouldn't change
    line_toend_src(test03, 3, src1); // shouldn't change
    line_toend_src(test10, 0, src2); // shouldn't change
    line_toend_src(test11, 0, src2); // shouldn't change
    line_toend_src(test12, 0, src2); // shouldn't change
    line_toend_src(test13, 0, src2); // shouldn't change
    line_toend_src(test20, 3, src3); // [0, 1, 2]
    line_toend_src(test21, 3, src3); // [1, 2, 3, 0, 1, 2]
    line_toend_src(test22, 3, src3); // shouldn't change
    line_toend_src(test23, 3, src3); // shouldn't change

    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test00, actual00), "00");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test01, actual01), "01");
    TEST_ASSERT_EQUAL_MESSAGE(actual02, test02, "02");
    TEST_ASSERT_EQUAL_MESSAGE(actual03, test03, "03");
    TEST_ASSERT_EQUAL_MESSAGE(NULL, test03->data, "03_0");
    TEST_ASSERT_EQUAL_MESSAGE(1, test03->len, "03_1");

    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test10, actual10), "10");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test11, actual11), "11");
    TEST_ASSERT_EQUAL_MESSAGE(actual12, test12, "12");
    TEST_ASSERT_EQUAL_MESSAGE(actual13, test13, "13");
    TEST_ASSERT_EQUAL_MESSAGE(NULL, test13->data, "13_0");
    TEST_ASSERT_EQUAL_MESSAGE(1, test13->len, "13_1");

    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test20, actual20), "20");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test21, actual21), "21");
    TEST_ASSERT_EQUAL_MESSAGE(actual22, test22, "22");
    TEST_ASSERT_EQUAL_MESSAGE(actual23, test23, "23");
    TEST_ASSERT_EQUAL_MESSAGE(NULL, test23->data, "23_0");
    TEST_ASSERT_EQUAL_MESSAGE(1, test23->len, "23_1");

    free_line(test00);
    free_line(test01);
    free_line(test10);
    free_line(test11);
    free_line(test20);
    free_line(test21);
    free_line(actual00);
    free_line(actual01);
    free_line(actual10);
    free_line(actual11);
    free_line(actual20);
    free_line(actual21);
}

void test_concat() 
{
    line test3_ = {1, NULL};

    line *test1 = line_make_eq(0, 0.);
    line *test2 = line_make(3, 1., 2., 3.);
    line *test3 = &test3_;
    line *test4 = NULL;

    line *res11 = line_concat(test1, test1);
    line *act11 = line_make(0);
    line *res12 = line_concat(test1, test2);
    line *act12 = line_make(3, 1., 2., 3.);
    line *res13 = line_concat(test1, test3);
    line *act13 = NULL;
    line *res14 = line_concat(test1, test4);
    line *act14 = NULL;
    line *res21 = line_concat(test2, test1);
    line *act21 = line_make(3, 1., 2., 3.);
    line *res22 = line_concat(test2, test2);
    line *act22 = line_make(6, 1., 2., 3., 1., 2., 3.);
    line *res23 = line_concat(test2, test3);
    line *act23 = NULL;
    line *res24 = line_concat(test2, test4);
    line *act24 = NULL;
    line *res31 = line_concat(test3, test1);
    line *act31 = NULL;
    line *res32 = line_concat(test3, test2);
    line *act32 = NULL;
    line *res33 = line_concat(test3, test3);
    line *act33 = NULL;
    line *res34 = line_concat(test3, test4);
    line *act34 = NULL;
    line *res41 = line_concat(test4, test1);
    line *act41 = NULL;
    line *res42 = line_concat(test4, test2);
    line *act42 = NULL;
    line *res43 = line_concat(test4, test3);
    line *act43 = NULL;
    line *res44 = line_concat(test4, test4);
    line *act44 = NULL;

    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res11, act11), "11");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res12, act12), "12");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res21, act21), "21");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res22, act22), "22");
    TEST_ASSERT_MESSAGE(res13 == act13, "13");
    TEST_ASSERT_MESSAGE(res14 == act14, "14");
    TEST_ASSERT_MESSAGE(res23 == act23, "23");
    TEST_ASSERT_MESSAGE(res24 == act24, "24");
    TEST_ASSERT_MESSAGE(res31 == act31, "31");
    TEST_ASSERT_MESSAGE(res32 == act32, "32");
    TEST_ASSERT_MESSAGE(res33 == act33, "33");
    TEST_ASSERT_MESSAGE(res34 == act34, "34");
    TEST_ASSERT_MESSAGE(res41 == act41, "41");
    TEST_ASSERT_MESSAGE(res42 == act42, "42");
    TEST_ASSERT_MESSAGE(res43 == act43, "43");
    TEST_ASSERT_MESSAGE(res44 == act44, "44");

    free_line(test1);
    free_line(test2);
    free_line(res11);
    free_line(act11);
    free_line(res12);
    free_line(act12);
    free_line(res21);
    free_line(act21);
    free_line(res22);
    free_line(act22);
}

double op_square(double val) { return val * val; }
void test_map() 
{
    line *test0 = line_make(4, 1., 2., 3., -4.);
    line *test1 = line_make(0);
    // line *test2 = NULL; In this case nothing happens, with line {1, NULL} too

    line_map(test0, op_square);
    line_map(test1, op_square);

    line *actual0 = line_make(4, 1., 4., 9., 16.);
    line *actual1 = line_make(0.);

    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test0, actual0), "0");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test1, actual1), "1");

    free_line(test0);
    free_line(actual0);
    free_line(test1);
    free_line(actual1);
}

int filter_gt_1(double val) { return val > 1 ? 1 : 0; }
void test_filter() 
{
    line *test0 = line_make(5, -1., 0.25, 3., -4., 5.67);
    line *test1 = line_make(0);
    // line *test2 = NULL; In this case nothing happens, with line {1, NULL} too

    int *res0 = line_filter(test0, filter_gt_1);
    int *res1 = line_filter(test1, filter_gt_1);
    int act0[5] = {0, 0, 1, 0, 1};
    int *act1 = NULL;

    short check0 = 0;
    for (size_t i = 0; i < test0->len; i++) {
        if (act0[i] != res0[i]) {
            check0 = 1;
            break;
        }
    }

    TEST_ASSERT_EQUAL_MESSAGE(0, check0, "0");
    TEST_ASSERT_EQUAL_MESSAGE(res1, act1, "1");

    free(res0);
    free(res1);
    free_line(test0);
    free_line(test1);
}

long double reduce_op_sum(long double v1, double v2) { return v1 + v2; }
void test_reduce() 
{
    line test4_ = {1, NULL};

    line *test0 = line_make(5, -1., 0.25, 3., -4., 5.67);
    line *test1 = line_make(0);
    line *test2 = line_make(1, 1.234);
    line *test3 = NULL;
    line *test4 = &test4_;

    long double res0 = line_reduce(test0, reduce_op_sum);
    long double res1 = line_reduce(test1, reduce_op_sum);
    long double res2 = line_reduce(test2, reduce_op_sum);
    long double res3 = line_reduce(test3, reduce_op_sum);
    long double res4 = line_reduce(test4, reduce_op_sum);

    long double act0 = 3.92;
    long double act1 = 0.;
    long double act2 = 1.234;
    long double act3 = 0.;
    long double act4 = 0.;

    TEST_ASSERT_EQUAL_MESSAGE(act0, res0, "0");
    TEST_ASSERT_EQUAL_MESSAGE(act1, res1, "1");
    TEST_ASSERT_EQUAL_MESSAGE(act2, res2, "2");
    TEST_ASSERT_EQUAL_MESSAGE(act3, res3, "3");
    TEST_ASSERT_EQUAL_MESSAGE(act4, res4, "4");

    free_line(test0);
    free_line(test1);
    free_line(test2);
}

int filter_lt_1(double val) { return val < 1 ? 1 : 0; }
void test_select()
{
    line *test0 = line_make(5, -1., 0.25, 3., -4., 5.67);
    line *test1 = line_make(0);

    line *res0 = line_select(test0, filter_lt_1);
    line *res1 = line_select(test1, filter_lt_1);

    line *act0 = line_make(3, -1., 0.25, -4.);
    line *act1 = line_make(0, 0.);

    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res0, act0), "0");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res1, act1), "1");

    free_line(test0);
    free_line(test1);
    free_line(res0);
    free_line(res1);
    free_line(act0);
    free_line(act1);
}

void test_slice() 
{
    line test0_ = {1, NULL};

    line *test0 = &test0_;
    line *test1 = NULL;
    line *test2 = line_make(0, 0.);
    line *test3 = line_make(1, 0.25);
    line *test4 = line_make(7, 1., 2., 3., 4., 5., 6., 7.);

    line *slice0 = line_slice(test0, 0, 0, 1); // []
    line *slice1 = line_slice(test1, 0, 0, 1); // []
    line *slice2 = line_slice(test2, 0, 0, 1); // []
    line *slice3 = line_slice(test3, 0, 0, 1); // [0.25]
    line *slice4 = line_slice(test3, 0, 0, 0); // [0.25]
    line *slice5 = line_slice(test3, 0, 0, -1); // [0.25]
    line *slice6 = line_slice(test4, 0, 6, 1);  // [1., 2., 3., 4., 5., 6., 7.]
    line *slice7 = line_slice(test4, 6, 0, -1);  // [7., 6., 5., 4., 3., 2., 1.]
    line *slice8 = line_slice(test4, 2, 5, 1);   // [3., 4., 5., 6.]
    line *slice9 = line_slice(test4, 2, 5, 2);   // [3., 5.]
    line *slice10 = line_slice(test4, 2, 5, -1);   // [3., 2., 1.]
    line *slice11 = line_slice(test4, 2, 5, 5);    // [3.]
    line *slice12 = line_slice(test4, 5, 2, 1);    // [6., 7.]
    line *slice13 = line_slice(test4, 5, 2, -1);   // [6., 5., 4., 3.]
    line *slice14 = line_slice(test4, 5, 2, -2);   // [6., 4.]
    line *slice15 = line_slice(test4, 5, 2, -10);   // [6.]
    line *slice16 = line_slice(test4, 10, 2, 1);    // []
    line *slice17 = line_slice(test4, 1, 20, 1);    // []
    line *slice18 = line_slice(test4, 7, 2, 1);    // []
    line *slice19 = line_slice(test4, 1, 7, 1);    // []
    line *slice20 = line_slice(test4, 1, 6, 0);    // [2.]

    line *act0 = line_make(0, 0.);
    line *act1 = line_make(0, 0.);
    line *act2 = line_make(0, 0.);
    line *act3 = line_make(1, 0.25);
    line *act4 = line_make(1, 0.25);
    line *act5 = line_make(1, 0.25);
    line *act6 = line_make(7, 1., 2., 3., 4., 5., 6., 7.);
    line *act7 = line_make(7, 7., 6., 5., 4., 3., 2., 1.);
    line *act8 = line_make(4, 3., 4., 5., 6.);
    line *act9 = line_make(2, 3., 5.);
    line *act10 = line_make(3, 3., 2., 1.);
    line *act11 = line_make(1, 3.);
    line *act12 = line_make(2, 6., 7.);
    line *act13 = line_make(4, 6., 5., 4., 3.);
    line *act14 = line_make(2, 6., 4.);
    line *act15 = line_make(1, 6.);
    line *act16 = line_make(0, 0.);
    line *act17 = line_make(0, 0.);
    line *act18 = line_make(0, 0.);
    line *act19 = line_make(0, 0.);
    line *act20 = line_make(1, 2.);

    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice0, act0), "0");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice1, act1), "1");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice2, act2), "2");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice3, act3), "3");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice4, act4), "4");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice5, act5), "5");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice6, act6), "6");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice7, act7), "7");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice8, act8), "8");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice9, act9), "9");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice10, act10), "10");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice11, act11), "11");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice12, act12), "12");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice13, act13), "13");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice14, act14), "14");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice15, act15), "15");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice16, act16), "16");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice17, act17), "17");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice18, act18), "18");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice19, act19), "19");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(slice20, act20), "20");

    free_line(test0);
    free_line(test1);
    free_line(test2);
    free_line(test3);
    free_line(test4);
    free_line(slice0);
    free_line(slice1);
    free_line(slice2);
    free_line(slice3);
    free_line(slice4);
    free_line(slice5);
    free_line(slice6);
    free_line(slice7);
    free_line(slice8);
    free_line(slice9);
    free_line(slice10);
    free_line(slice11);
    free_line(slice12);
    free_line(slice13);
    free_line(slice14);
    free_line(slice15);
    free_line(slice16);
    free_line(slice17);
    free_line(slice18);
    free_line(slice19);
    free_line(slice20);
    free_line(act0);
    free_line(act1);
    free_line(act2);
    free_line(act3);
    free_line(act4);
    free_line(act5);
    free_line(act6);
    free_line(act7);
    free_line(act8);
    free_line(act9);
    free_line(act10);
    free_line(act11);
    free_line(act12);
    free_line(act13);
    free_line(act14);
    free_line(act15);
    free_line(act16);
    free_line(act17);
    free_line(act18);
    free_line(act19);
    free_line(act20);
}

double combine_op_sum(double v1, double v2) { return v1 + v2; }
void test_combine() 
{
    line test0_ = {1, NULL}; 

    line *test0 = &test0_;
    line *test1 = NULL;
    line *test2 = line_make(0, 0.);
    line *test3 = line_make(1, 0.25);
    line *test4 = line_make(1, 3.25);
    line *test5 = line_make(7, 1., 2., 3., 4., 5., 6., 7.);

    line *res0 = line_combine(test0, test1, combine_op_sum); // NULL
    line *res1 = line_combine(test1, test2, combine_op_sum); // NULL
    line *res2 = line_combine(test2, test2, combine_op_sum); // []
    line *res3 = line_combine(test2, test3, combine_op_sum); // NULL
    line *res4 = line_combine(test3, test4, combine_op_sum); // [3.5]
    line *res5 = line_combine(test5, test3, combine_op_sum); // NULL
    line *res6 = line_combine(test5, test5, combine_op_sum); // [2., 4., 6., 8., 10., 12., 14.]

    line *act2 = line_make(0, 0.);
    line *act4 = line_make(1, 3.5);
    line *act6 = line_make(7, 2., 4., 6., 8., 10., 12., 14.);

    TEST_ASSERT_NULL_MESSAGE(res0, "0");
    TEST_ASSERT_NULL_MESSAGE(res1, "1");
    TEST_ASSERT_NULL_MESSAGE(res3, "3");
    TEST_ASSERT_NULL_MESSAGE(res5, "5");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res2, act2), "2");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res4, act4), "4");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(res6, act6), "6");

    free_line(test2);
    free_line(test3);
    free_line(test4);
    free_line(test5);
    free_line(res2);
    free_line(res4);
    free_line(res6);
    free_line(act2);
    free_line(act4);
    free_line(act6);
}

void test_copy() 
{
    line test0_ = {1, NULL};

    line *test0 = &test0_;
    line *test1 = NULL;
    line *test2 = line_make(0, 0.);
    line *test3 = line_make(1, 0.25);
    line *test4 = line_make(1, 3.25);
    line *test5 = line_make(7, 1., 2., 3., 4., 5., 6., 7.);

    line *res0 = line_copy(test0);
    line *res1 = line_copy(test1);
    line *res2 = line_copy(test2);
    line *res3 = line_copy(test3);
    line *res4 = line_copy(test4);
    line *res5 = line_copy(test5);

    TEST_ASSERT_NULL_MESSAGE(res0, "0");
    TEST_ASSERT_NULL_MESSAGE(res1, "1");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test2, res2), "2");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test3, res3), "3");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test4, res4), "4");
    TEST_ASSERT_EQUAL_MESSAGE(0, line_compare(test5, res5), "5");

    free_line(test2);
    free_line(test3);
    free_line(test4);
    free_line(test5);
}

void test_print() {
    // There are no actual tests here, this func is called just to check how it all looks
    line test0_ = {1, NULL};

    line *test0 = &test0_;
    line *test1 = NULL;
    line *test2 = line_make(0, 0.);
    line *test3 = line_make(1, 0.25);
    line *test4 = line_make(1, 3.25);
    line *test5 = line_make(7, 1., 2., 3., 4., 5., 6., 7.);

    // Yes, line_print doesn't add newlines, it should work like that
    puts("\n\ntest0 line: SHOULD BE NULL");
    line_print(test0);
    puts("\n\ntest1 line: SHOULD BE NULL");
    line_print(test1);
    puts("\n\ntest2 line: []");
    line_print(test2);
    puts("\n\ntest3 line: [0.25]");
    line_print(test3);
    puts("\n\ntest4 line: [3.25]");
    line_print(test4);
    puts("\n\ntest5 line: [1., 2., 3., 4., 5., 6., 7.]");
    line_print(test5);

    free_line(test2);
    free_line(test3);
    free_line(test4);
    free_line(test5);
    puts("\n");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_make);
    RUN_TEST(test_compare);
    RUN_TEST(test_toend);
    RUN_TEST(test_concat);
    RUN_TEST(test_map);
    RUN_TEST(test_reduce);
    RUN_TEST(test_filter);
    RUN_TEST(test_select);
    RUN_TEST(test_slice);
    RUN_TEST(test_combine);
    RUN_TEST(test_copy);
    RUN_TEST(test_print);
    return UNITY_END();
}