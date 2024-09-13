#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  big_decimal big_value = to_big(value);
  bool source_sign = check_sign(value.bits[3]);
  int scale = get_scale(big_value.bits[7]);
  if (scale > 0) {
    for (int i = 0; i < scale; i++) {
      big_value = big_div10(big_value);
    }
  }
  *result = from_big(big_value);
  set_sign(&result->bits[3], source_sign);
  return OK;
}