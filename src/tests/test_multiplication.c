// #include "test.h"

// START_TEST(simple_mul) {
//   s21_decimal value_1 = {
//       {2, 0, 0, 0}};
//   s21_decimal value_2 = {
//       {3, 0, 0, 0}};
//   s21_decimal result = {{0}};
//   int error = s21_mul(value_1, value_2, &result);
//   s21_decimal expected = {{6, 0, 0, 0}};
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result.bits[i], expected.bits[i]);
//   }
//   ck_assert_int_eq(error, 0);

// }
// END_TEST

// START_TEST(simple_mul_negative) {
//   s21_decimal value_1 = {
//       {14, 0, 0, 1 << 31}};
//   s21_decimal value_2 = {
//       {22, 0, 0, 0}};
//   s21_decimal result = {{0}};
//   int error = s21_mul(value_1, value_2, &result);
//   s21_decimal expected = {{308, 0, 0, 1 << 31}};
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result.bits[i], expected.bits[i]);
//   }
//   ck_assert_int_eq(error, 0);

// }
// END_TEST

// START_TEST(mul_negative) {
//   s21_decimal value_1 = {{0, 1, 0, 1 << 31}};
//   s21_decimal value_2 = {{100, 0, 0, 1 << 31}};
//   s21_decimal result = {{0}};
//   int error = s21_mul(value_1, value_2, &result);
//   s21_decimal expected = {{0, 100, 0, 0}};
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result.bits[i], expected.bits[i]);
//   }
//   ck_assert_int_eq(error, 0);

// }
// END_TEST

// START_TEST(mul_negative_2) {
//   s21_decimal value_1 = {{0, 0, 4, 1 << 31}};
//   s21_decimal value_2 = {{1024, 0, 0, 1 << 31}};
//   s21_decimal result = {{0}};
//   int error = s21_mul(value_1, value_2, &result);
//   s21_decimal expected = {{0, 0, 4096, 0}};
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result.bits[i], expected.bits[i]);
//   }
//   ck_assert_int_eq(error, 0);

// }

// END_TEST
// START_TEST(mul_negative_overword) {
//   s21_decimal value_1 = {{1073741824, 0, 0, 1 << 31}};
//   s21_decimal value_2 = {{8, 0, 0, 0}};
//   s21_decimal result = {{0}};
//   int error = s21_mul(value_1, value_2, &result);
//   s21_decimal expected = {{0, 2, 0, 1 << 31}};
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result.bits[i], expected.bits[i]);
//   }
//   ck_assert_int_eq(error, 0);

// }
// END_TEST

// START_TEST(mul_overflow) {
//   s21_decimal value_1 = {{0, 0, 1, 0}};
//   s21_decimal value_2 = {{4294967295, 1, 0, 0}};
//   s21_decimal result = {{0}};

//   int error = s21_mul(value_1, value_2, &result);
//   ck_assert_int_eq(error, 1);

//   s21_decimal value_3 = {{0, 0, 4294967295, 0}};
//   s21_decimal value_4 = {{11, 0, 0, 0}};
//   s21_decimal result2 = {{0}};

//   error = s21_mul(value_3, value_4, &result2);
//   ck_assert_int_eq(error, 1);
// }
// END_TEST

// START_TEST(mul_with_scale) {
//   s21_decimal value_1 = {{100, 0, 0, 2 << 16}};
//   s21_decimal value_2 = {{50, 0, 0, 1 << 16}};
//   s21_decimal result = {{0}};
//   s21_decimal expected = {{5000, 0, 0, 3 << 16}};

//   int error = s21_mul(value_1, value_2, &result);
//   ck_assert_int_eq(error, 0);
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result.bits[i], expected.bits[i]);
//   }

//   s21_decimal value_3 = {{1000, 0, 0, 12 << 16}};
//   s21_decimal value_4 = {{0, 0, 123, 8 << 16}};
//   s21_decimal result2 = {{0}};
//   s21_decimal expected2 = {{0, 0, 123000, 20 << 16}};

//   error = s21_mul(value_3, value_4, &result2);
//   ck_assert_int_eq(error, 0);
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result2.bits[i], expected2.bits[i]);
//   }
// }
// END_TEST

// // банковское округление не работает:
// // START_TEST(mul_bank_round) {
// //   s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
// //   s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
// //   s21_decimal result;
// //   int code = s21_mul(decimal1, decimal2, &result);

// //   ck_assert_int_ne(code, 0);
// // }
// // END_TEST



// Suite *tests_functions(void) {
//   Suite *s = suite_create("Mul");
//   TCase *tc_core = tcase_create("Core");

//   tcase_add_test(tc_core, simple_mul);
//   tcase_add_test(tc_core, simple_mul_negative);
//   tcase_add_test(tc_core, mul_negative);
//   tcase_add_test(tc_core, mul_negative_2);
//   tcase_add_test(tc_core, mul_negative_overword);
//   tcase_add_test(tc_core, mul_overflow);
//   tcase_add_test(tc_core, mul_with_scale);
// //   tcase_add_test(tc_core, mul_bank_round);


//   suite_add_tcase(s, tc_core);
//   return s;
// }