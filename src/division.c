// #include <stdbool.h>
// #include <stdio.h>

// #include "s21_decimal.h"

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   // Умножать 1 на 10, пока не станет больше, чем 2, добавлять по 1 в порядок
//   // Найти старший бит 1 числа
//   // Найти старший бит 2 числа
//   // Сдвинуть 1 число до уравнивания старших бит
//   // Записать количество сдвигов?? Да!
//   // Вычесть из n цифр 1 числа n цифр второго и получить остаток
//   // Если вычитается, записать 1 в результат
//   // Снести цифру, после n цифр первого числа и добавить к остатку (можно
//   // делать, сколько было сдвигов) Дописать в конец результата 1 или 0 (вычлось
//   // или нет)(дописываь при кажом сносе)(зациклить) Вычесть из n цифр 1 числа n
//   // цифр остатка и получить новый остаток Конечный остаток умножать на 10
//   // (добавляя в порядок) и повторять весь процесс.
//   big_decimal divisible = to_big(value_1);
//   big_decimal divider = to_big(value_2);
//   big_decimal tmp = {{0, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal tmp_2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
//   big_decimal tmp_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
//   if (is_not_null(divisible) && is_not_null(divider)) {
//   } else {
//   };  // return
//   int res = OK;
//   int width_1 = 0;
//   int width_2 = 0;
//   int fix_shift_big = 0;
//   // get width
//   for (int i = 32 * 7; i >= 0 && !width_1; i--) {
//     if (check_bit(divisible, i)) width_1 = i;
//   }
//   for (int i = 32 * 7; i >= 0 && !width_2; i--) {
//     if (check_bit(divider, i)) width_2 = i;
//   }
//   // set width and scale



//   while (is_not_null(divisible) && get_scale(divisible.bits[7]) < 29) {
//     while ((width_2 > width_1 || big_is_less(divisible, divider)) &&
//            get_scale(divisible.bits[7]) < 29) 
//            {
//             printf("%d before --- \n", get_scale(divisible.bits[7]));
//       divisible = big_x10(divisible);
//       set_scale(&divisible.bits[7], fix_shift_big);
//       // printf("%d =-=- \n", fix_shift_big);
//       printf("%d after --- \n", get_scale(divisible.bits[7]));
//       set_scale(&divisible.bits[7], (get_scale(divisible.bits[7]) + 1));
//       // printf("%d === \n", get_scale(divisible.bits[7]));
//       fix_shift_big = get_scale(divisible.bits[7]);
//     }

//     // Test for inf must be here!

//   printf("%d +++ \n", get_scale(divisible.bits[7]));
//     tmp = shift_big_decimal(divisible, width_1 - width_2, 'R');
    
//     divisible = shift_big_decimal(divisible, 32 * 7 - width_1 - width_2, 'L');
//     divisible = shift_big_decimal(divisible, 32 * 7 - width_1 - width_2, 'R');

//     tmp_res = shift_big_decimal(tmp_res, 1, 'L');
//     set_bit(&tmp_res, 1, is_not_null(tmp_2) ? 1 : 0);

//     tmp_2 = big_minus_big(tmp, divider);
//     divisible = big_plus_big(divisible,
//                              shift_big_decimal(tmp_2, width_1 - width_2, 'L'));
//   }

//   if (0) {
//     res = TOO_BIG;
//   } else if (0) {
//     res = TOO_LITTLE;
//   } else if (0) {
//     res = DIV_BY_ZERO;
//   }
//   return res;
// }