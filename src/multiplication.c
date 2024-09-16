#include <limits.h>

#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;
  if (result) {
    bool result_sign =
        check_sign(value_1.bits[3]) ^ check_sign(value_2.bits[3]);
    int result_exponent =
        get_scale(value_1.bits[3]) + get_scale(value_2.bits[3]);

    big_decimal temp_result = {{0}};
    unsigned long long overflow_word = 0;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        unsigned long long temp =
            (unsigned long long)value_1.bits[i] * value_2.bits[j] +
            overflow_word + temp_result.bits[i + j];
        temp_result.bits[i + j] = temp & UINT_MAX;
        overflow_word = temp >> 32;
      }
      temp_result.bits[i + 3] += overflow_word;
      overflow_word = 0;
    }

    // big_decimal remainder = {{0}};
    // big_decimal garb = {{0}};
    // remainder = big_div10(temp_result, &garb);

    // while (result_exponent > 0 && (remainder.bits[0] == 0)) {
    //     big_div10(temp_result, &temp_result);
    //     result_exponent--;
    // }

    // big_decimal remainder = {{0}};
    // big_decimal divider = {{10}};
    // big_decimal garb = {{0}};
    // while ((result_exponent > 28)) {
    //   // remainder = big_div_big(temp_result, divider, &garb);
    //   remainder = big_div_big(temp_result, divider, &temp_result);
    //   // if (temp_result.bits[2] == 0 && temp_result.bits[1] == 0 &&
    //   temp_result.bits[0] == 0) {
    //   //   *res = CONVERT_ERROR;
    //   // } else
    //   if (remainder.bits[0] > 5 || ((temp_result.bits[0] & 1) &&
    //   (remainder.bits[0] == 5))) {
    //     temp_result.bits[0]++;  // надо прибавить 1 через сложение
    //   }
    //   result_exponent--;
    // }

    // remainder = big_div_big(temp_result, divider, &garb);
    // while ((result_exponent > 0) && (remainder.bits[0] == 0)) {
    //   // remainder = big_div_big(temp, divider, &garb);
    //   remainder = big_div_big(temp_result, divider, &temp_result);
    //   result_exponent--;
    // }

    // int remainder = 0;
    // while (result_exponent > 28 || (temp_result.bits[3] && result_exponent))
    // {
    //   unsigned long long temp = 0;
    //   // remainder = temp_result.bits[0] % 10;
    //   for (int i = 5; i >= 0; --i) {
    //     temp = (temp << 32) | temp_result.bits[i];
    //     temp_result.bits[i] = temp / 10;
    //     temp = temp % 10;
    //   }
    //   // if ((temp_result.bits[0] & 1) && (remainder == 5))
    //   // temp_result.bits[0]++;  //банковское округление
    //   result_exponent--;
    // }

    set_scale(&temp_result.bits[7], result_exponent);
    set_sign(&temp_result.bits[7], result_sign);
    res = can_convert(temp_result);
    if (res == OK) {
      *result = from_big(temp_result);
    }

    // }
    // if (temp_result.bits[5] != 0 || temp_result.bits[4] != 0 ||
    //     temp_result.bits[3] != 0) {
    //   res = 1;
    // }

    // if (temp_result.bits[2] == 0 && temp_result.bits[1] == 0 &&
    //     temp_result.bits[0] == 0 && result_exponent == 28) {
    //   res = TOO_BIG;
    // }

    // for (int i = 0; i < 3; i++) {
    //   result->bits[i] = temp_result.bits[i];
    // }

    // set_sign(&result->bits[3], result_sign);
    // set_scale(&result->bits[3], result_exponent);
  } else
    res = 1;
  return res;
}