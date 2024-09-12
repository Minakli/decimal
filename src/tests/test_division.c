#include "test.h"

START_TEST(test_division_insert_1) {
  s21_decimal a = {{368, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal c = {{0, 0, 0, 0}};
  ck_assert_int_eq(get_scale(c.bits[3]), 0);
  ck_assert_int_eq(s21_div(a, b, &c), 0);
  ck_assert_int_eq(get_scale(c.bits[3]), 1);
  ck_assert_int_eq(c.bits[0], 736);
}
END_TEST

START_TEST(test_division_insert_2) {
  big_decimal a = {{365, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal b = {{5, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal d = big_div_big(a, b, &c);
  ck_assert_int_eq(d.bits[0], 0);
  ck_assert_int_eq(c.bits[0], 73);
}
END_TEST

START_TEST(test_division_insert_3) {
  big_decimal a = {{3680, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal b = {{5, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal d = big_div_big(a, b, &c);
  ck_assert_int_eq(d.bits[0], 0);
  ck_assert_int_eq(c.bits[0], 736);
}
END_TEST

START_TEST(test_division_insert_4) {
  big_decimal a = {{1000001, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal b = {{100000, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal d = big_div_big(a, b, &c);
  ck_assert_int_eq(d.bits[0], 1);
  ck_assert_int_eq(c.bits[0], 10);
}
END_TEST

Suite *tests_division(void) {
  Suite *s = suite_create("Division");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_division_insert_1);
  tcase_add_test(tc_core, test_division_insert_2);
  tcase_add_test(tc_core, test_division_insert_3);
  tcase_add_test(tc_core, test_division_insert_4);

  suite_add_tcase(s, tc_core);
  return s;
}