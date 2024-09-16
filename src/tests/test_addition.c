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
  big_decimal a = {{0b10100100110001100111111111111111, 0b111000110101111110, 0,
                    0, 0, 0, 0, 0}};
  big_decimal b = {{0b10100100110001100111111111111111, 0b111000110101111110, 0,
                    0, 0, 0, 0, 0}};
  big_decimal c = {{0b01001001100011001111111111111110, 0b1110001101011111101,
                    0, 0, 0, 0, 0, 0}};
  big_decimal d = big_plus_big(a, b);
  ck_assert_int_eq(d.bits[0], c.bits[0]);
  ck_assert_int_eq(d.bits[1], c.bits[1]);
}
END_TEST

START_TEST(test_addition_4) {
  // 7.9228162514264337593543950335
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  // 7.9228162514264337593543950335
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal c = {{0, 0, 0, 0}};
  s21_sub(a, b, &c);
  // 0
  s21_decimal expected = {{0, 0, 0, 0x1b0000}};

  ck_assert_int_eq(c.bits[0], expected.bits[0]);
  ck_assert_int_eq(c.bits[1], expected.bits[1]);
  ck_assert_int_eq(c.bits[2], expected.bits[2]);
}
END_TEST

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
  tcase_add_test(tc_core, test_addition_4);

  suite_add_tcase(s, tc_core);
  return s;
}