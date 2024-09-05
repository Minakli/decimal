#include <limits.h>

#include "test.h"

START_TEST(dec_to_int_simple) {
  s21_decimal value = {{144, 0, 0, 0}};
  int result = 0;
  int expected = 144;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_simple_negative) {
  s21_decimal value = {{INT_MAX, 0, 0, 1 << 31}};
  int result = 0;
  int expected = INT_MIN + 1;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int) {
  s21_decimal value = {{INT_MAX, 0, 0, 0}};
  int result = 0;
  int expected = INT_MAX;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_scale) {
  s21_decimal value = {{9999999, 0, 0, 2 << 16}};
  int result = 0;
  int expected = 99999;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
  //   Уточнение про преобразование из числа типа decimal в тип int:
  // Если в числе типа decimal есть дробная часть, то её следует отбросить
  // (например, 0.9 преобразуется 0).
}
END_TEST

START_TEST(dec_to_int_overflow_error) {
  s21_decimal value = {{123124, 1, 0, 0}};
  int result = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dec_to_int_overflow_error_2) {
  s21_decimal value = {{2147483648, 0, 0, 0}};
  int result = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dec_to_int_small) {
  s21_decimal value = {{9999999, 0, 0, 7 << 16}};
  int result = 0;
  int expected = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_too_small) {
  s21_decimal value = {{9999999, 0, 0, 29 << 16}};
  int result = 0;
  int expected = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dec_to_int_big_and_scale) {
  s21_decimal value = {{0, 1, 0, 1 << 16}};
  int result = 0;
  int expected = 429496729;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_large_with_scale) {
  s21_decimal value = {{0, 11, 0, 7 << 16}};
  int result = 0;
  int expected = 4724;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_too_large_with_scale) {
  s21_decimal value = {{0, 0, 1, 16 << 16}};
  int result = 0;
  int expected = 1844;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_edge_negative_scale) {
  s21_decimal value = {{123456789, 0, 0, (7 << 16) | (1 << 31)}};
  int result = 0;
  int expected = -12;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_simple) {
  int value = 11;
  s21_decimal result = {{0}};
  s21_decimal expected = {{11, 0, 0, 0}};
  ;
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_max) {
  int value = INT_MAX;
  s21_decimal result = {{0}};
  s21_decimal expected = {{INT_MAX, 0, 0, 0}};
  ;
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_min) {
  int value = INT_MIN;
  s21_decimal result = {{0}};
  s21_decimal expected = {{2147483648, 0, 0, 1 << 31}};
  ;
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_negative) {
  int value = -123145;
  s21_decimal result = {{0}};
  s21_decimal expected = {{123145, 0, 0, 1 << 31}};
  ;
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

END_TEST
Suite *tests_converters(void) {
  Suite *s = suite_create("converters");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, dec_to_int_simple);
  tcase_add_test(tc_core, dec_to_int_simple_negative);
  tcase_add_test(tc_core, dec_to_int);
  tcase_add_test(tc_core, dec_to_int_scale);
  tcase_add_test(tc_core, dec_to_int_overflow_error);
  tcase_add_test(tc_core, dec_to_int_overflow_error_2);
  tcase_add_test(tc_core, dec_to_int_small);
  tcase_add_test(tc_core, dec_to_int_too_small);
  tcase_add_test(tc_core, dec_to_int_big_and_scale);
  tcase_add_test(tc_core, dec_to_int_large_with_scale);
  tcase_add_test(tc_core, dec_to_int_too_large_with_scale);
  tcase_add_test(tc_core, dec_to_int_edge_negative_scale);
  tcase_add_test(tc_core, int_to_dec_simple);
  tcase_add_test(tc_core, int_to_dec_max);
  tcase_add_test(tc_core, int_to_dec_min);
  tcase_add_test(tc_core, int_to_dec_negative);
  suite_add_tcase(s, tc_core);
  return s;
}
