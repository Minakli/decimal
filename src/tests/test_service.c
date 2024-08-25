#include "test.h"

// bool check_bit(s21_decimal a, int num);
// void set_bit(s21_decimal *a, int num, bool choice);
// void print_decimal(s21_decimal a); ---------------------------------
// bool check_sign(s21_decimal a);
// void set_sign(s21_decimal *a, bool choice);
// int get_scale(s21_decimal a);
// void set_scale(s21_decimal *a, int num);
// bool is_not_null(s21_decimal a);

START_TEST(test_func_insert_1) {
    s21_decimal a = {{
      0b00000000000000000000000000100011,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000
    }};
    int num_1 = 0;
    int num_2 = 1;
    int num_3 = 3;
    int num_4 = 5;
    ck_assert_int_eq(check_bit(a, num_1), 1);
    ck_assert_int_eq(check_bit(a, num_2), 1);
    ck_assert_int_eq(check_bit(a, num_3), 0);
    ck_assert_int_eq(check_bit(a, num_4), 1);
    }
END_TEST

START_TEST(test_func_insert_2) {
    s21_decimal a = {{
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000
    }};
    int num = 2;
    set_bit(&a, num, true);
    ck_assert_int_eq(a.bits[0], 4);
    }
END_TEST

START_TEST(test_func_insert_3) {
    s21_decimal a = {{
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000001
    }};
    ck_assert_int_eq(check_sign(a), true);
    }
END_TEST

START_TEST(test_func_insert_4) {
    s21_decimal a = {{
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000
    }};
    ck_assert_int_eq(check_sign(a), false);
    set_sign(&a, true);
    ck_assert_int_eq(check_sign(a), true);
    }
END_TEST


START_TEST(test_func_insert_5) {
    s21_decimal a = {{
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000110000000001
    }};
    ck_assert_int_eq(get_scale(a), 12);
    }
END_TEST

START_TEST(test_func_insert_6) {
    s21_decimal a = {{
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000110000000001
    }};
    ck_assert_int_eq(get_scale(a), 12);
    set_scale(&a, 25);
    ck_assert_int_eq(get_scale(a), 25);
    }
END_TEST

START_TEST(test_func_insert_7) {
    s21_decimal a = {{
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000
    }};
    ck_assert_int_eq(is_not_null(a), 0);
    set_bit(&a, 55, true);
    ck_assert_int_eq(is_not_null(a), 1);
    }
END_TEST

START_TEST(test_func_insert_8) {
    big_decimal a = {{
      0b00000000000000000000000000000111,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000
    }};
    ck_assert_int_eq(a.bits[0], 7);
    ck_assert_int_eq(shift_big_decimal(a, 31, 'L').bits[0], 2147483648);
    ck_assert_int_eq(shift_big_decimal(a, 32, 'L').bits[0], 0);
    ck_assert_int_eq(shift_big_decimal(a, 32, 'L').bits[1], 7);
}
END_TEST

Suite *tests_functions(void) {
  Suite *s = suite_create("Functions");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_func_insert_1);
  tcase_add_test(tc_core, test_func_insert_2);
  tcase_add_test(tc_core, test_func_insert_3);
  tcase_add_test(tc_core, test_func_insert_4);
  tcase_add_test(tc_core, test_func_insert_5);
  tcase_add_test(tc_core, test_func_insert_6);
  tcase_add_test(tc_core, test_func_insert_7);
  tcase_add_test(tc_core, test_func_insert_8);

  suite_add_tcase(s, tc_core);
  return s;
}