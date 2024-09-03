#include <stdbool.h>
#include <stdio.h>

#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Умножать 1 на 10, пока не станет больше, чем 2, добавлять по 1 в порядок
  // Найти старший бит 1 числа
  // Найти старший бит 2 числа
  // Сдвинуть 1 число до уравнивания старших бит
  // Записать количество сдвигов?? Да!
  // Вычесть из n цифр 1 числа n цифр второго и получить остаток
  // Если вычитается, записать 1 в результат
  // Снести цифру, после n цифр первого числа и добавить к остатку (можно
  // делать, сколько было сдвигов) Дописать в конец результата 1 или 0 (вычлось
  // или нет)(дописываь при кажом сносе)(зациклить) Вычесть из n цифр 1 числа n
  // цифр остатка и получить новый остаток Конечный остаток умножать на 10
  // (добавляя в порядок) и повторять весь процесс.
  big_decimal divisible = to_big(value_1);
  big_decimal divider = to_big(value_2);
  big_decimal tmp = {{0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal tmp_res = to_big(*result);
  int res = OK;
  int max_bit_1 = 0, max_bit_2 = 0;
  for (int i = 32 * 7 - 1; i >= 0 && !max_bit_1; i--) {
    if (check_bit(divisible, i)) max_bit_1 = i;
  }
  for (int i = 32 * 7 - 1; i >= 0 && !max_bit_2; i--) {
    if (check_bit(divider, i)) max_bit_1 = 2;
  }
  // if(max_bit_1 >= max_bit_2) {
  // s21_sub_big(shift_big_decimal(divisible, max_bit_1 - max_bit_2, 'R'),
  // divider,  &tmp);
  shift_big_decimal(tmp_res, 1, 'L');
  set_bit(&tmp_res, 0, true);
  // } else
  // if(is_not_null(tmp)){}

  if (0) {
    res = TOO_BIG;
  } else if (0) {
    res = TOO_LITTLE;
  } else if (0) {
    res = DIV_BY_ZERO;
  }
  return res;
}