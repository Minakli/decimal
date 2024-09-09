#include <limits.h>

#include "test.h"

START_TEST(dec_to_int_simple) {
  s21_decimal value = {{144, 0, 0, 0}};
  int result = 0;
  int expected = 144;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_simple_negative) {
  s21_decimal value = {{INT_MAX, 0, 0, 1 << 31}};
  int result = 0;
  int expected = INT_MIN + 1;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int) {
  s21_decimal value = {{INT_MAX, 0, 0, 0}};
  int result = 0;
  int expected = INT_MAX;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_scale) {
  s21_decimal value = {{9999999, 0, 0, 2 << 16}};
  int result = 0;
  int expected = 99999;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
  //   Уточнение про преобразование из числа типа decimal в тип int:
  // Если в числе типа decimal есть дробная часть, то её следует отбросить
  // (например, 0.9 преобразуется 0).
}
END_TEST

START_TEST(dec_to_int_overflow_error) {
  s21_decimal value = {{123124, 1, 0, 0}};
  int result = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dec_to_int_overflow_error_2) {
  s21_decimal value = {{2147483648, 0, 0, 0}};
  int result = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dec_to_int_small) {
  s21_decimal value = {{9999999, 0, 0, 7 << 16}};
  int result = 0;
  int expected = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_too_small) {
  s21_decimal value = {{9999999, 0, 0, 29 << 16}};
  int result = 0;
  int expected = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(dec_to_int_big_and_scale) {
  s21_decimal value = {{0, 1, 0, 1 << 16}};
  int result = 0;
  int expected = 429496729;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_large_with_scale) {
  s21_decimal value = {{0, 11, 0, 7 << 16}};
  int result = 0;
  int expected = 4724;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_too_large_with_scale) {
  s21_decimal value = {{0, 0, 1, 16 << 16}};
  int result = 0;
  int expected = 1844;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_to_int_edge_negative_scale) {
  s21_decimal value = {{123456789, 0, 0, (7 << 16) | (1 << 31)}};
  int result = 0;
  int expected = -12;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(result, expected);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_simple) {
  int value = 11;
  s21_decimal result = {{0}};
  s21_decimal expected = {{11, 0, 0, 0}};
  ;
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_max) {
  int value = INT_MAX;
  s21_decimal result = {{0}};
  s21_decimal expected = {{INT_MAX, 0, 0, 0}};
  ;
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_min) {
  int value = INT_MIN;
  s21_decimal result = {{0}};
  s21_decimal expected = {{2147483648, 0, 0, 1 << 31}};
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(int_to_dec_negative) {
  int value = -123145;
  s21_decimal result = {{0}};
  s21_decimal expected = {{123145, 0, 0, 1 << 31}};
  int error = s21_from_int_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_round) {
  float value = 12.34567;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1234567, 0, 0, 5 << 16}};
  int error = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(float_round_2) {
  float value = 1234567.1234567;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1234567, 0, 0, 0 << 16}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_round_3) {
  float value = 0.000001;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 6 << 16}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_0) {
  float value = 10.0;
  s21_decimal result = {{0}};
  s21_decimal expected = {{10, 0, 0, 0}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_1) {
  float value = -1230.0;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1230, 0, 0, 1 << 31}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

// START_TEST(float_small_error) {  // Если числа слишком малы (0 < |x| <
// 1e-28),
//                                  // возвращай ошибку и значение, равное 0.
//   float value = 0.00000000000000000000000000001;
//   s21_decimal result = {{0}};
//   s21_decimal expected = {{0, 0, 0, 0}};
//   int error = s21_from_float_to_decimal(value, &result);
//   ck_assert_int_eq(error, 1);
//   for (int i = 0; i < 4; i++) {
//     ck_assert_int_eq(result.bits[i], expected.bits[i]);
//   }
// }

END_TEST

START_TEST(float_small) {
  float value = 0.0000000000000000000000000001;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 28 << 16}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_scale) {
  float value = -0.0000000123456789123;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1234568, 0, 0, 14 << 16 | 1 << 31}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_scale_2) {
  float value = 87432.12345;
  s21_decimal result = {{0}};
  s21_decimal expected = {{8743212, 0, 0, 2 << 16}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_scale_fail) {
  float value = 5294967296.12345;
  s21_decimal result = {{0}};
  s21_decimal expected = {{999999704, 1, 0, 0}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_negative_scale) {
  float value = 2.0 * 4294967296.0 * 4294967296.0;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1449992192, 431, 2, 0}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_negative_scale_2) {
  float value = 12345678099876543456773.463;
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xB4880000, 0x42BA35C8, 0x0000029D, 0}};
  int error = s21_from_float_to_decimal(value, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(float_negative_scale_3) {
  // START_TEST(s21_ftd_import_tests) {
  // 12345678099876543456773.463 = 12345680000000000000000.0 =
  // {{0xB4880000, 0x42BA35C8, 0x0000029D, 0}};
  float value = 12345678099876543456773.463;
  s21_decimal result4 = {{0}};
  s21_decimal expected4 = {{0xB4880000, 0x42BA35C8, 0x0000029D, 0}};

  int error = s21_from_float_to_decimal(value, &result4);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result4.bits[i], expected4.bits[i]);
  }

  // -0.00001234E28 = {{0x83200000, 0x8703F6C7, 0x00001A21, 0x80000000}};
  value = -0.00001234E28;
  s21_decimal result5 = {{0}};
  s21_decimal expected5 = {{0x83200000, 0x8703F6C7, 0x00001A21, 0x80000000}};

  error = s21_from_float_to_decimal(value, &result5);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result5.bits[i], expected5.bits[i]);
  }

  // 8.4E-28 = {{0x00000008, 0x00000000, 0x00000000, 0x001C0000}};
  value = 8.4E-28;
  s21_decimal result6 = {{0}};
  s21_decimal expected6 = {{0x00000008, 0x00000000, 0x00000000, 0x001C0000}};

  error = s21_from_float_to_decimal(value, &result6);
  for (int i = 3; i >= 0; i--) {
    ck_assert_int_eq(result6.bits[i], expected6.bits[i]);
  }
  ck_assert_int_eq(error, 0);

  // -0.0000001234985690E17 = {{0xE01BE8A0, 0x00000002, 0, 0x80000000}};
  value = -0.0000001234985690E17;
  s21_decimal result7 = {{0}};
  s21_decimal expected7 = {{0xE01BE8A0, 0x00000002, 0, 0x80000000}};

  error = s21_from_float_to_decimal(value, &result7);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result7.bits[i], expected7.bits[i]);
  }

  // 79228162514264337593543950335E-28 = {{0x0078E480, 0, 0, 0x00060000}};
  value = 79228162514264337593543950335E-28;
  s21_decimal result8 = {{0}};
  s21_decimal expected8 = {{0x0078E480, 0, 0, 0x00060000}};

  error = s21_from_float_to_decimal(value, &result8);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result8.bits[i], expected8.bits[i]);
  }
}
END_TEST

START_TEST(s21_itd_simple) {
  // 1 = {1, 0, 0, 0}
  int number = 1;
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0}};

  int error = s21_from_int_to_decimal(number, &result);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }

  // 2147483647 = {2,147,483,647, 0, 0, 0}
  number = 2147483647;
  s21_decimal result2 = {{0}};
  s21_decimal expected2 = {{2147483647, 0, 0, 0}};

  error = s21_from_int_to_decimal(number, &result2);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result2.bits[i], expected2.bits[i]);
  }

  // -2147483648 = {2147483648, 0, 0, 1U << 31}
  number = -2147483648;
  s21_decimal result3 = {{0}};
  s21_decimal expected3 = {{2147483648, 0, 0, 1U << 31}};

  error = s21_from_int_to_decimal(number, &result3);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result3.bits[i], expected3.bits[i]);
  }
}
END_TEST

START_TEST(s21_dti_simple) {
  // {1, 0, 0, 0} = 1
  s21_decimal value = {{1, 0, 0, 0}};
  int result = 0;
  int expected = 1;

  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result, expected);

  // {2147483647, 0, 0, 0} = 2147483647
  s21_decimal value2 = {{2147483647, 0, 0, 0}};
  int result2 = 0;
  int expected2 = 2147483647;

  error = s21_from_decimal_to_int(value2, &result2);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result2, expected2);

  // {2147483648, 0, 0, 1U << 31} = -2147483648
  s21_decimal value3 = {{2147483648, 0, 0, 1 << 31}};
  int result3 = 0;
  int expected3 = -2147483648;

  error = s21_from_decimal_to_int(value3, &result3);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result3, expected3);
}
END_TEST

START_TEST(s21_dti_overflow) {
  // {2147483648, 0, 0, 0} = 2147483648 > INT_MAX
  s21_decimal value = {{2147483648, 0, 0, 0}};
  int result = 0;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(error, 1);

  // {0, 1, 0, 0} = 4294967296 > int32
  s21_decimal value2 = {{0, 1, 0, 0}};
  int result2 = 0;
  error = s21_from_decimal_to_int(value2, &result2);
  ck_assert_int_eq(error, 1);

  // {2147483649, 0, 0, 1U << 31} = -2147483649 > int32
  s21_decimal value3 = {{5, 0, 0, 1U << 31}};
  int result3 = 0;
  error = s21_from_decimal_to_int(value3, &result3);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_dti_scale) {
  // {1000, 0, 0, 2 << 16} = 10.00 = 10
  s21_decimal value = {{1000, 0, 0, 2 << 16}};
  int result = 0;
  int expected = 10;
  int error = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(result, expected);

  // {5, 0, 0, 29} = scale > DECIMAL_SCALE_MAX_VALUE
  s21_decimal value2 = {{5, 0, 0, 29 << 16}};
  int result2 = 0;
  int error2 = s21_from_decimal_to_int(value2, &result2);
  ck_assert_int_eq(error2, 1);

  //   {34567, 0, 0, 3 << 16 || 1U << 31} =
  //   -34.567 = -34
  s21_decimal value3 = {{34567, 0, 0, (3 << 16) | (1U << 31)}};
  int result3 = 0;
  int expected3 = -34;
  int error3 = s21_from_decimal_to_int(value3, &result3);
  ck_assert_int_eq(error3, 0);
  ck_assert_int_eq(result3, expected3);

  // {0, 1, 0, 1U << 31} = 429496729.6 = 429496729
  s21_decimal value4 = {{0, 1, 0, 1 << 16}};
  int result4 = 0;
  int expected4 = 429496729;
  int error4 = s21_from_decimal_to_int(value4, &result4);
  ck_assert_int_eq(error4, 0);
  ck_assert_int_eq(result4, expected4);
}
END_TEST

END_TEST
Suite *tests_converters(void) {
  Suite *s = suite_create("converters");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, dec_to_int_simple);
  tcase_add_test(tc_core, dec_to_int_simple_negative);
  tcase_add_test(tc_core, dec_to_int);
  tcase_add_test(tc_core, dec_to_int_scale);
  tcase_add_test(tc_core, dec_to_int_overflow_error);
  tcase_add_test(tc_core, dec_to_int_overflow_error_2);
  tcase_add_test(tc_core, dec_to_int_small);
  tcase_add_test(tc_core, dec_to_int_too_small);
  tcase_add_test(tc_core, dec_to_int_big_and_scale);
  tcase_add_test(tc_core, dec_to_int_large_with_scale);
  tcase_add_test(tc_core, dec_to_int_too_large_with_scale);
  tcase_add_test(tc_core, dec_to_int_edge_negative_scale);
  tcase_add_test(tc_core, int_to_dec_simple);
  tcase_add_test(tc_core, int_to_dec_max);
  tcase_add_test(tc_core, int_to_dec_min);
  tcase_add_test(tc_core, int_to_dec_negative);
  tcase_add_test(tc_core, float_round);
  tcase_add_test(tc_core, float_round_2);
  tcase_add_test(tc_core, float_round_3);
  tcase_add_test(tc_core, float_0);
  tcase_add_test(tc_core, float_1);
  // tcase_add_test(tc_core, float_small_error);
  tcase_add_test(tc_core, float_small);
  tcase_add_test(tc_core, float_scale);
  tcase_add_test(tc_core, float_scale_2);
  tcase_add_test(tc_core, float_scale_fail);
  tcase_add_test(tc_core, float_negative_scale);
  tcase_add_test(tc_core, float_negative_scale_2);
  tcase_add_test(tc_core, float_negative_scale_3);
  tcase_add_test(tc_core, s21_dti_scale);
  tcase_add_test(tc_core, s21_itd_simple);
  tcase_add_test(tc_core, s21_dti_simple);
  tcase_add_test(tc_core, s21_dti_overflow);

  suite_add_tcase(s, tc_core);
  return s;
}
