#include <limits.h>

#include "s21_decimal.h"

// bool is_negative(s21_decimal value) { return value.bits[3] >> 31; }

// int get_exponent(s21_decimal value) { return ((value.bits[3] >> 16) & 255); }
//
// void set_exponent(s21_decimal *value, int exponent) {
//   value->bits[3] &= (1 << 31);
//   value->bits[3] |= ((exponent & 255) << 16);
// }

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  short error_status = 0;

  bool result_sign = check_sign(value_1.bits[3]) ^ check_sign(value_2.bits[3]);
  int result_exponent = get_scale(value_1.bits[3]) + get_scale(value_2.bits[3]);

  big_decimal temp_result = {{0}};
  unsigned long long overflow_word = 0;

  if (!result)
    error_status = -1;
  else {
    for (short i = 0; i < 3; ++i) {
      for (short j = 0; j < 3; ++j) {
        unsigned long long temp =
            (unsigned long long)value_1.bits[i] * value_2.bits[j] +
            overflow_word + temp_result.bits[i + j];
        temp_result.bits[i + j] = temp & UINT_MAX;
        overflow_word = temp >> 32;
      }
      temp_result.bits[i + 3] += overflow_word;
      overflow_word = 0;
    }
  }

  while (result_exponent > 28 || (temp_result.bits[3] && result_exponent)) {
    unsigned long long temp = 0;
    for (int i = 5; i >= 0; --i) {
      temp = (temp << 32) | temp_result.bits[i];
      temp_result.bits[i] = temp / 10;
      temp = temp % 10;
    }
    result_exponent--;
  }

  if (temp_result.bits[5] != 0 || temp_result.bits[4] != 0 ||
      temp_result.bits[3] != 0) {
    error_status = 1;
  }

  if (temp_result.bits[2] == 0 && temp_result.bits[1] == 0 &&
      temp_result.bits[0] == 0 && result_exponent == 28) {
    error_status = 2;
  }

  for (short i = 0; i < 3; i++) {
    result->bits[i] = temp_result.bits[i];
  }

  set_sign(&result->bits[3], result_sign);
  set_scale(&result->bits[3], result_exponent);

  return error_status;
}