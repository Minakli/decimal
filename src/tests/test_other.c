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

START_TEST(test_negate_1) {
  s21_decimal value = {{1, 0, 0, 2 << 16}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 2 << 16}};
  set_sign(&expected.bits[3], true);
  int error = s21_negate(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_negate_2) {
  // -46
  s21_decimal value = {{0x2e, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {{0}};
  // +46
  s21_decimal expected = {{0x2e, 0x0, 0x0, 0x0}};
  int error = s21_negate(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_negate_3) {
  // 0
  s21_decimal value = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result = {{0}};
  // 0
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x80000000}};
  int error = s21_negate(value, &result);
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
  tcase_add_test(tc_core, test_negate_1);
  tcase_add_test(tc_core, test_negate_2);
  tcase_add_test(tc_core, test_negate_3);

  suite_add_tcase(s, tc_core);
  return s;
}