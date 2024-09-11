#include "s21_decimal.h"

big_decimal big_div_big(big_decimal divisible, big_decimal divider,
                        big_decimal *result) {
  // big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0}};

  // int delta = get_width(divisible) - get_width(divider);
  int delta = get_width(divisible) + 1;
  // watch_32_binary(delta);

  // big_decimal remainder = shift_big_decimal(divisible, delta, 'R');
  big_decimal remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};

  while (delta) {
    remainder = shift_big_decimal(remainder, 1, 'L');
    set_bit(&remainder, 0, check_bit(divisible, delta - 1));
    delta--;
    if (big_is_greater_or_equal(remainder, divider)) {
      remainder = big_minus_big(remainder, divider);
      *result = shift_big_decimal(*result, 1, 'L');
      set_bit(result, 0, 1);
    } else {
      // set_bit(&remainder, 0, check_bit(divisible, delta--));
      *result = shift_big_decimal(*result, 1, 'L');
    }
  }
  //   if (big_is_greater_or_equal(remainder, divider)) {
  //     remainder = big_minus_big(remainder, divider);
  //     *result = shift_big_decimal(*result, 1, 'L');
  //     set_bit(result, 0, 1);
  //     remainder = shift_big_decimal(remainder, 1, 'L');
  //     set_bit(&remainder, 0, check_bit(divisible, delta--));
  //   } else {
  //     remainder = shift_big_decimal(remainder, 1, 'L');
  //     set_bit(&remainder, 0, check_bit(divisible, delta--));
  //     *result = shift_big_decimal(*result, 1, 'L');
  //     // print_32_binary(remainder.bits[0]);
  //   }
  //     printf("remainder :");
  //     print_32_binary(remainder.bits[0]);
  //     printf("result :");
  //     print_32_binary(result->bits[0]);
  // }
  return remainder;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal divisible = to_big(value_1);
  // big_decimal divisible_tmp = to_big(value_1);
  big_decimal divider = to_big(value_2);
  // big_decimal remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  // big_decimal tmp_2 = {{0, 0, 0, 0, 0, 0, 0, 0}};

  if (is_not_null(divisible) && is_not_null(divider)) {
  } else {
  };  // return
  int res = OK;
  int width_1 = 0;
  int width_2 = 0;
  int fix_shift_big = 0;

  while ((width_2 > width_1 || mantissa_is_less(divisible, divider)) &&
         get_scale(divisible.bits[7]) < 28) {
    divisible = big_x10(divisible);
    set_scale(&divisible.bits[7], (get_scale(divisible.bits[7]) + 1));
    width_1 = get_width(divisible);
  }

  int scale_1 = get_scale(divisible.bits[7]);
  int scale_2 = get_scale(divider.bits[7]);

  set_scale(&(divisible.bits[7]), 0);
  set_scale(&(divider.bits[7]), 0);

  if (0) {
    res = TOO_BIG;
  } else if (0) {
    res = TOO_LITTLE;
  } else if (0) {
    res = DIV_BY_ZERO;
  }
  return res;
}