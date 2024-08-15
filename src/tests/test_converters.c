#include "test.h"

START_TEST(test_converters_from_int) { printf("testzxc!\n"); }
END_TEST

Suite *tests_converters(void) {
  Suite *s = suite_create("converters");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_converters_from_int);

  suite_add_tcase(s, tc_core);
  return s;
}
