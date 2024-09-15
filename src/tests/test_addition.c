#include "test.h"

START_TEST(test_addition_1) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal c = {{0, 0, 0, 0}};
  int error = s21_add(a, b, &c);
  s21_decimal expected = {{5, 0, 0, 0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(c.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_addition_2) {
  // 7.9228162514264337593543950335
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int error = s21_add(a, b, &c);

  s21_decimal expected = {{0x33333333, 0x33333333, 0x33333333, 0x1b0000}};
  // 15.845632502852867518708790067
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(c.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_addition_3) {
  // 7.9228162514264337593543950335
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  // 7.922816251426433759354395033
  s21_decimal b = {{0x99999999, 0x99999999, 0x19999999, 0x1b0000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int error = s21_add(a, b, &c);
  // 15.845632502852867518708790066
  s21_decimal expected = {{0x33333332, 0x33333333, 0x33333333, 0x1b0000}};

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(c.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

// START_TEST(test_add_insert_3) {
//   big_decimal a = {{3680, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal b = {{5, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal d = big_div_big(a, b, &c);
//   ck_assert_int_eq(d.bits[0], 0);
//   ck_assert_int_eq(c.bits[0], 736);
// }
// END_TEST

// START_TEST(test_add_insert_4) {
//   big_decimal a = {{1000001, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal b = {{100000, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal d = big_div_big(a, b, &c);
//   ck_assert_int_eq(d.bits[0], 1);
//   ck_assert_int_eq(c.bits[0], 10);
// }
// END_TEST

Suite *tests_add(void) {
  Suite *s = suite_create("Addition");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_addition_1);
  tcase_add_test(tc_core, test_addition_2);
  tcase_add_test(tc_core, test_addition_3);

  suite_add_tcase(s, tc_core);
  return s;
}