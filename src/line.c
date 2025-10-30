#include "line.h"

line *line_copy(line *l) {
    if (l == NULL || l->data == NULL) 
    {
        return NULL;
    }
    if (l->len == 0) {
        return line_make(0, 0.);
    }
    double *ptr = malloc(sizeof(double) * l->len);
    if (ptr == NULL) {
        return NULL;
    }
    line *res = malloc(sizeof(line));
    if (res == NULL) {
        return NULL;
    }
    res->data = ptr;
    for (size_t i = 0; i < l->len; i++) {
        res->data[i] = l->data[i];
    }
    res->len = l->len;
    return res;
}

line *line_make_eq(size_t len, double value)
{
    double *ptr = malloc(sizeof(double) * len);
    if (ptr == NULL)
    {
        return NULL;
    }
    line *res = malloc(sizeof(line));
    if (res == NULL)
    {
        return NULL;
    }
    res->len = len;
    for (size_t i = 0; i < len; i++)
    {
        ptr[i] = value;
    }
    res->data = ptr;
    return res;
}

line *line_make(size_t len, ...)
{
    double *ptr = malloc(sizeof(double) * len);
    if (ptr == NULL)
    {
        return NULL;
    }
    line *res = malloc(sizeof(line));
    if (res == NULL)
    {
        return NULL;
    }
    res->len = len;
    va_list factor;
    // Getting variadic arguments values (we're supposing they're double)
    va_start(factor, len);
    for (size_t i = 0; i < len; i++)
    {
        ptr[i] = va_arg(factor, double);
    }
    va_end(factor);
    res->data = ptr;
    return res;
}

line *line_make_src(size_t len, double *src)
{
    double *ptr = malloc(sizeof(double) * len);
    if (ptr == NULL)
    {
        return NULL;
    }
    line *res = malloc(sizeof(line));
    if (res == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < len; i++)
    {
        ptr[i] = src[i];
    }
    res->data = ptr;
    res->len = len;
    return res;
}

short line_compare(line *l1, line *l2)
{
    if (l1 == NULL || l2 == NULL || l1->data == NULL || l2->data == NULL) 
    {
        return -2;
    }
    if (l1->len > l2->len)
    {
        return 1;
    }
    if (l2->len > l1->len)
    {
        return 2;
    }
    // Now we know that len1 = len2
    if (l1->len == 0) {
        return 0;
    }
    short res = 0;
    for (size_t i = 0; i < l1->len; i++) {
        if (l1->data[i] != l2->data[i]) {
            res = -1;
            break;
        }
    }
    return res;
}

line *line_slice(line *l, size_t from, size_t to, int step)
{
    // !!! 'to' is included into result
    // Incorrect input -> empty result
    if (l == NULL || l->data == NULL || from >= l->len || to >= l->len)
    {
        return line_make(0, 0);
    }
    // Not really sure what to return when step = 0, guess data[from] will do
    if (from == to || step == 0)
    {
        return line_make(1, l->data[from]);
    }
    // I suppose, line could be big, so first I'll count result length
    int mult = 1;
    if (from > to)
    {
        mult = -1;
    }
    long long long_to = to * mult;
    size_t res_len = 0;
    for (long long i = from; mult * i <= long_to && i > -1 && i < (long long)l->len; i += step)
    {
        res_len++;
    }
    line *res = line_make_eq(res_len, 0);
    if (res == NULL)
    {
        return line_make(0, 0);
    }
    size_t j = 0;
    for (long long i = from; mult * i <= long_to && i > -1 && i < (long long)l->len; i += step)
    {
        res->data[j] = l->data[i];
        j++;
    }
    return res;
}

void free_line(line *l)
{
    if (l == NULL || l->data == NULL)
        return;
    free(l->data);
    free(l); // all line_make* functions dynamically allocate memory
}

void line_toend_src(line *l, size_t src_len, double *src)
{
    if (l == NULL || l->data == NULL || src == NULL || src_len == 0)
        return;
    size_t new_len = l->len + src_len;
    l->data = realloc(l->data, new_len * sizeof(double));
    // Yes, if realloc() fails, data will be lost
    for (size_t i = 0; i < src_len; i++)
    {
        l->data[l->len + i] = src[i];
    }
    l->len = new_len;
}

line *line_concat(line *l1, line *l2)
{
    if (l1 == NULL ||
        l2 == NULL ||
        l1->data == NULL ||
        l2->data == NULL)
    {
        return NULL;
    }
    size_t len_sum = l1->len + l2->len;
    double *ptr = malloc(sizeof(double) * len_sum);
    if (ptr == NULL)
    {
        return NULL;
    }
    line *res = malloc(sizeof(line));
    if (res == NULL)
    {
        return NULL;
    }
    res->len = len_sum;
    for (size_t i = 0; i < len_sum; i++)
    {
        if (i < l1->len)
        {
            ptr[i] = l1->data[i];
        }
        else
        {
            ptr[i] = l2->data[i - l1->len];
        }
    }
    res->data = ptr;
    return res;
}

void line_map(line *l, double (*op)(double))
{
    if (l == NULL || l->data == NULL)
        return;
    for (size_t i = 0; i < l->len; i++)
    {
        l->data[i] = op(l->data[i]);
    }
}

int *line_filter(line *l, int (*filter)(double))
{
    // filter returns int for a reason: user could want to get more states, not only true/false
    if (l == NULL || l->data == NULL || filter == NULL || l->len == 0)
        return NULL;
    int *res = malloc(sizeof(int) * l->len);
    if (res == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < l->len; i++)
    {
        res[i] = filter(l->data[i]);
    }
    return res;
}

size_t mask_count(size_t len, int *mask)
{
    if (mask == NULL)
    {
        return 0;
    }
    size_t res = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (mask[i] != 0)
        {
            res++;
        }
    }
    return res;
}

line *line_select(line *l, int (*filter)(double))
{
    if (l == NULL || l->data == NULL || filter == NULL)
        return NULL;
    int *mask = line_filter(l, filter);
    if (mask == NULL)
    {
        return line_make(0, 0.);
    }
    // Here we don't care if filter returns something except 0/1. Every non-zero value we include into result
    size_t res_len = mask_count(l->len, mask);
    double res_data[res_len];
    size_t j = 0;
    for (size_t i = 0; i < l->len; i++)
    {
        if (mask[i])
        {
            res_data[j] = l->data[i];
            j++;
        }
    }
    free(mask);
    line *res = line_make_src(res_len, res_data);
    return res;
}

long double line_reduce(line *l, long double (*op)(long double, double))
{
    // Maybe op should handle len=0 and len=1 cases?
    if (l == NULL || l->data == NULL || l->len == 0)
        return 0;
    if (l->len == 1)
        return l->data[0];
    long double res = l->data[0];
    for (size_t i = 1; i < l->len; i++)
    {
        res = op(res, l->data[i]);
    }
    return res;
}

double line_reduce_d(line *l, double (*op)(double, double))
{
    // Maybe op should handle len=0 and len=1 cases?
    if (l == NULL || l->data == NULL || l->len == 0)
        return 0;
    if (l->len == 1)
        return l->data[0];
    double res = l->data[0];
    for (size_t i = 1; i < l->len; i++)
    {
        res = op(res, l->data[i]);
    }
    return res;
}

line *line_combine(line *l1, line *l2, double (*op)(double, double))
{
    if (l1 == NULL ||
        l2 == NULL ||
        l1->data == NULL ||
        l2->data == NULL ||
        l1->len != l2->len)
    {
        return NULL;
    }
    if (l1->len == 0) {
        return line_make(0, 0.);
    }
    line *res = line_make_eq(l1->len, 0);
    if (res == NULL)
        return res;
    for (size_t i = 0; i < l1->len; i++)
    {
        res->data[i] = op(l1->data[i], l2->data[i]);
    }
    return res;
}

void line_print(line *l)
{
    if (l == NULL)
    {
        fputs("NULL pointer passed to line_print", stdout);
        return;
    }
    double *ptr = l->data;
    if (ptr == NULL)
    {
        fputs("NULL pointer in arr->data passed to line_print", stdout);
        return;
    }
    fputs("line: ", stdout);
    if (l->len == 0)
    {
        fputs("[]", stdout);
        return;
    }
    fputs("[ ", stdout);
    for (size_t i = 0; i < l->len - 1; i++)
    {
        printf("%lf, ", ptr[i]);
    }
    printf("%lf ]", ptr[l->len - 1]);
}