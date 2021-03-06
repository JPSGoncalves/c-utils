#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"
#include "strlib.h"

GLOBAL_STRING_DEF(test_str, 8);

int test_print_info_string(const char *msg, string_t *s)
{
	printf("\t[%s] s->len: %d s->max_len: %d s->buf: %s\n",
		msg, s->len, s->max_len, s->buf);
}

int test_check_str(string_t *s, const char *str)
{
	if (strcmp(s->buf, str) != 0)
		return -1;

	return 0;
}

int test_str_printf()
{
	int ret;

	ret = str_printf(&test_str, "c", "age: %d", 10);
	if (ret <= 0 || test_check_str(&test_str, "age: 10")) {
		printf("\tret: %d", ret);
		test_print_info_string("str_printf: create", &test_str);
		return -1;
	}

	ret = str_printf(&test_str, "a", " id: %d", 101);
	if (ret != -1) {
		printf("\tret: %d", ret);
		test_print_info_string("str_printf: create", &test_str);
		return -1;
	}

	return 0;
}

int test_str_copy()
{
	int ret;

	ret = str_copy(&test_str, "c", "1234567890", 10);
	if (ret != -1) {
		test_print_info_string("Create excess", &test_str);
		return -1;
	}

	ret = str_copy(&test_str, "cf", "1234567890", 10);
	if (ret != 8) {
		test_print_info_string("Create fill", &test_str);
		return -1;
	}

	ret = str_copy(&test_str, "c", "1234567", 7);
	if (ret != 7) {
		test_print_info_string("Create", &test_str);
		return -1;
	}

	ret = str_copy(&test_str, "a", "1", 1);
	if (ret != 1) {
		test_print_info_string("Append", &test_str);
		return -1;
	}

	ret = str_copy(&test_str, "a", "123", 3);
	if (ret != -1) {
		test_print_info_string("Apend after full", &test_str);
		return -1;
	}

	return 0;
}

void do_test_strlib(test_result_t *result)
{
	int total=0, pass=0;

	if (test_str_copy() == 0) pass++; total++;
	if (test_str_printf() == 0) pass++; total++;

	result->pass += pass;
	result->total += total;
}
