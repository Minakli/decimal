#include <limits.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  bool error_status = false;
  if (dst) {
    for (short i = 0; i < 4; dst->bits[i++] = 0);
    if (src < 0) {
      dst->bits[3] |= (1 << 31);
      src = -src;
    }
    dst->bits[0] = src;
  } else
    error_status = true;

  return error_status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  bool error_status = false;
  unsigned int exponent = get_scale(src.bits[3]);
  if (exponent > 28) error_status = true;

  //   Проверка что все неиспльзуемые биты равны нулю
  //   if ((src.bits[3] & 0x7F00FFFF) != 0) error_status = true;

  if (!dst)
    error_status = true;
  else {
    for (short i = exponent; i > 0; --i) {
      unsigned long long int temp = src.bits[2] % 10;
      src.bits[2] /= 10;

      temp = (temp << 32) | src.bits[1];
      src.bits[1] = temp / 10;

      temp = ((temp % 10) << 32) | src.bits[0];
      src.bits[0] = temp / 10;
    }

    // is overflow
    if (src.bits[2] != 0 || src.bits[1] != 0 || src.bits[0] > INT_MAX ||
        (check_sign(src.bits[3]) && src.bits[0] > INT_MAX)) {
      error_status = true;
      *dst = 0;
    }

    *dst = check_sign(src.bits[3]) ? -src.bits[0] : src.bits[0];
  }

  return error_status;
}
