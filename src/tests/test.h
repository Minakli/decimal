#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "../s21_decimal.h"

Suite *tests_converters(void);

Suite *tests_division(void);

Suite *tests_functions(void);

Suite *tests_mul(void);

Suite *tests_add(void);

#endif