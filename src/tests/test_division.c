// #include "test.h"

// START_TEST(test_division_insert_1) {
//   s21_decimal a = {
//       {0b00000000000000000000000000000001, 0b00000000000000000000000000000000,
//        0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
//   s21_decimal b = {{100, 500, 1000, 10000000}};
//   s21_decimal c = {
//       {0b00000000000000000000000000000000, 0b00000000000000000000000000000000,
//        0b00000000000000000000000000000000, 0b00000000000000000000000000000000}};
//   ck_assert_int_eq(s21_div(a, b, &c), 0);
// }
// END_TEST

// Suite *tests_division(void) {
//   Suite *s = suite_create("Division");
//   TCase *tc_core = tcase_create("Core");

//   tcase_add_test(tc_core, test_division_insert_1);

//   suite_add_tcase(s, tc_core);
//   return s;
// }