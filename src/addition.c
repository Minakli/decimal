#include "s21_decimal.h"

// Сложить два положительных числа одного порядка
big_decimal big_plus_big(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {0};
  int memory = 0, sum = 0;
  for (int i = 0; i < 32 * 7; i++) {
    sum = check_bit(value_1, i) + check_bit(value_2, i) + memory;
    memory = sum > 1 ? 1 : 0;
    set_bit(&result, i, sum % 2);
  }
  return result;
}
big_decimal big_minus_big(big_decimal value_1, big_decimal value_2) {
  // Вычесть одно из второго, положительные одного порядка
  big_decimal result = {0};
  int debt = 0, sum = 0;
  for (int i = 0; i < 32 * 7; i++) {
    sum = check_bit(value_1, i) - check_bit(value_2, i) - debt;
    debt = sum < 0 ? 1 : 0;
    set_bit(&result, i, sum % 2);
  }
}
void normalization(big_decimal value_1, big_decimal value_2) {
  // Определить, где больше порядок
  // Привести меньший порядок к большему
  int delta = get_scale(value_1.bits[7]) - get_scale(value_2.bits[7]);
  if (delta > 0) {
    for (; delta > 0; delta--) {
    }
  }
}