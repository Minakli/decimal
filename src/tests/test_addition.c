#include "test.h"

// big_decimal big_plus_big(big_decimal value_1, big_decimal value_2)
// big_decimal big_minus_big(big_decimal value_1, big_decimal value_2)

START_TEST(test_add_insert_1) {
  big_decimal value_1 = {{2, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{1, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_3 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  value_3 = big_plus_big(value_1, value_2);
  ck_assert_int_eq(value_1.bits[0], 2);
  ck_assert_int_eq(value_2.bits[0], 1);
  // printf("%d --\n", value_3.bits[0]);
  // ck_assert_int_eq(value_3.bits[0], 3);
}
END_TEST

Suite *tests_add(void) {
  Suite *s = suite_create("Add");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_add_insert_1);

  suite_add_tcase(s, tc_core);
  return s;
}