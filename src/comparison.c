#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = check_sign(value_1.bits[3]);
  int sign2 = check_sign(value_2.bits[3]);
  bool is_equal = false;
  big_decimal big_value_1 = to_big(value_1);
  big_decimal big_value_2 = to_big(value_2);
  normalization(&big_value_1, &big_value_2);
  if ((sign1 == sign2) &&
      (big_mantissa_is_equal(big_value_1, big_value_2) == 1)) {
    is_equal = true;
  }
  return is_equal;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = check_sign(value_1.bits[3]);
  int sign2 = check_sign(value_2.bits[3]);
  bool is_greater = false;
  big_decimal big_value_1 = to_big(value_1);
  big_decimal big_value_2 = to_big(value_2);
  normalization(&big_value_1, &big_value_2);
  if (sign1 != sign2) {
    is_greater = (sign1 < sign2);
  } else {
    is_greater = big_mantissa_is_greater(big_value_1, big_value_2);
    if (sign1 == 1) {
      is_greater = !is_greater;
    }
  }
  return is_greater;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater(value_1, value_2) &&
         s21_is_not_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}