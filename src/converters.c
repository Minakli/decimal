#include <limits.h>
#include <math.h>  //надо вынести в хедер
#include <string.h>

#include "s21_decimal.h"

s21_decimal increase_scale_to_zero(s21_decimal src, int *source_scale);

s21_decimal decrease_scale_to_zero(s21_decimal src, int *source_scale);

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  bool error_status = false;
  if (dst) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    if (src < 0) {
      bool result_sign = true;
      set_sign(&dst->bits[3], result_sign);
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

  if (!dst)
    error_status = true;
  else {
    for (int i = exponent; i > 0; --i) {
      unsigned long long int temp = src.bits[2] % 10;
      src.bits[2] /= 10;

      temp = (temp << 32) | src.bits[1];
      src.bits[1] = temp / 10;

      temp = ((temp % 10) << 32) | src.bits[0];
      src.bits[0] = temp / 10;
    }

    // is overflow
    if (src.bits[2] != 0 || src.bits[1] != 0 ||
        src.bits[0] > (INT_MAX + check_sign(src.bits[3]))) {
      error_status = true;
      *dst = 0;
    }

    *dst = check_sign(src.bits[3]) ? -src.bits[0] : src.bits[0];
  }

  return error_status;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  bool error_status = false;
  bool scale_sign = false;
  int source_scale = 0;
  char string_source[16] = {0};
  if (isinf(src) || isnan(src)) {
    error_status = true;
  }
  if (!error_status) {
    snprintf(string_source, 16, "%e", src);
    for (int i = 0; string_source[i]; i++) {
      if (string_source[i] == '-') {
        bool result_sign = true;
        set_sign(&dst->bits[3], result_sign);
        i++;
      }
      if (string_source[i] != 'e' && string_source[i] != '.') {
        dst->bits[0] = dst->bits[0] * 10 + (string_source[i] - '0');
      } else if (string_source[i] == 'e') {
        i++;
        if (string_source[i] == '-') {
          scale_sign = true;
        }
        i++;
        if ((string_source[i] >= '0' && string_source[i] <= '9')) {
          source_scale = (string_source[i] - '0') * 10;
          i++;
          source_scale += (string_source[i] - '0');
          i++;
        }
      }
    }
  }
  if (!scale_sign) {
    source_scale = -source_scale;
  }
  source_scale += 6;

  *dst = increase_scale_to_zero(*dst, &source_scale);
  *dst = decrease_scale_to_zero(*dst, &source_scale);
  // *dst = increase_scale_to_zero(*dst, &source_scale);

  if (dst->bits[2] == 0 && dst->bits[1] == 0 && dst->bits[0] == 0 &&
      source_scale != 0) {
    error_status = true;
  }

  if (source_scale >= 0 && source_scale <= 28) {
    set_scale(&dst->bits[3], source_scale);
  } else {
    error_status = true;
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
  }

  return error_status;
}

s21_decimal increase_scale_to_zero(s21_decimal src, int *source_scale) {
  while (*source_scale < 0) {
    s21_decimal multiplier = {{10, 0, 0, 0}};
    s21_mul(src, multiplier, &src);
    (*source_scale)++;
  }
  return src;
}

s21_decimal decrease_scale_to_zero(s21_decimal src, int *source_scale) {
  while (((*source_scale > 0) && ((src.bits[0] % 10) == 0)) ||
         (*source_scale > 28)) {
    unsigned int remainder = 0;
    for (int i = 2; i >= 0; --i) {
      unsigned long long temp =
          ((unsigned long long)remainder << 32) | src.bits[i];
      src.bits[i] = temp / 10;
      remainder = temp % 10;
    }
    (*source_scale)--;
  }
  return src;
  // return increase_scale_to_zero(src, source_scale);
}