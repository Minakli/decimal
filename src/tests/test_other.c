#include "test.h"

START_TEST(test_truncate_1) {
  s21_decimal value = {{123, 123, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{123, 123, 0, 0}};

  int error = s21_truncate(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal value = {{123, 0, 0, 2 << 16}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0}};

  int error = s21_truncate(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_truncate_3) {
  s21_decimal value = {{723, 0, 0, 2 << 16}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{7, 0, 0, 0}};

  int error = s21_truncate(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *tests_other(void) {
  Suite *s = suite_create("Other");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_truncate_1);
  tcase_add_test(tc_core, test_truncate_2);
  tcase_add_test(tc_core, test_truncate_3);

  suite_add_tcase(s, tc_core);
  return s;
}