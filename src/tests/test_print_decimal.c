#include <string.h>

#include "test.h"

START_TEST(test_print_decimal) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  char buffer[1024];
  print_decimal(a, buffer, sizeof(buffer));
  char expected_output[] = "79228162514264337593543950335";
  ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_print_decimal_2) {
  s21_decimal a = {{0x66666667, 0x66666666, 0x26666666, 0x1B0000}};
  char buffer[1024];
  print_decimal(a, buffer, sizeof(buffer));
  char expected_output[] = "2.9754671443";
  // ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_print_decimal_3) {
  s21_decimal a = {{3, 0, 0, 0}};
  char buffer[1024];
  print_decimal(a, buffer, sizeof(buffer));
  char expected_output[] = "3";
  ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_print_decimal_4) {
  s21_decimal a = {{0xFFFFFFFF, 0, 0, 0}};
  char buffer[1024];
  print_decimal(a, buffer, sizeof(buffer));
  char expected_output[] = "4294967295";
  ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_print_decimal_5) {
  s21_decimal a = {{10, 0, 0, 0x80000000}};
  char buffer[1024];
  print_decimal(a, buffer, sizeof(buffer));
  char expected_output[] = "-10";
  // ck_assert_str_eq(buffer, expected_output);
}
END_TEST

Suite *tests_print_decimal(void) {
  Suite *s = suite_create("Print");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_print_decimal);
  tcase_add_test(tc_core, test_print_decimal_2);
  tcase_add_test(tc_core, test_print_decimal_3);
  tcase_add_test(tc_core, test_print_decimal_4);
  tcase_add_test(tc_core, test_print_decimal_5);
  suite_add_tcase(s, tc_core);
  return s;
}