#include "s21_decimal.h"

void print_32_binary(int a) {
  printf("-- ");
  for (int i = 31; i > -1; i--) {
    printf("%d", (a >> i) & 1);
  }
  printf("\n");
}

void print_binary(big_decimal a) {
  for (int i = 0; i < 7; i++) print_32_binary(a.bits[i]);
}

bool check_bit(big_decimal a, int num) {
  return (a.bits[num / 32] >> (num % 32)) & 1 ? true : false;
}

void set_bit(big_decimal *a, int num, int choice) {
  a->bits[num / 32] = choice ? a->bits[num / 32] | (1 << (num % 32))
                             : a->bits[num / 32] & ~(1 << (num % 32));
}

bool check_sign(int value) { return ((value >> 31) & 1) ? true : false; }

void set_sign(int *value, bool choice) {
  *value = choice ? *value | (choice << 31) : *value & ~(1 << 31);
}

int get_scale(int value) { return (value >> 16) & 255; }

void set_scale(int *value, int num) {
  *value = (((*value >> 16) & 0b1000000000000000) | num) << 16;
}

bool is_not_null(big_decimal a) {
  return (a.bits[0] == a.bits[1] == a.bits[2] == a.bits[3] == a.bits[4] ==
          a.bits[5] == a.bits[6] == 0)
             ? false
             : true;
}

big_decimal shift_big_decimal(big_decimal a, int value, char vector) {
  unsigned memory = 0, tmp = 0;
  while (value > 0) {
    if (vector == 'L') {
      for (int i = 0; i < 7; i++) {
        tmp = a.bits[i];
        a.bits[i] <<= (value > 31 ? 31 : value);
        a.bits[i] |= memory;
        memory = tmp >> (32 - (value > 31 ? 31 : value));
      }
    } else if (vector == 'R') {
      for (int i = 6; i >= 0; i++) {
        tmp = a.bits[i];
        a.bits[i] >>= (value > 31 ? 31 : value);
        a.bits[i] |= memory;
        memory = tmp << (32 - (value > 31 ? 31 : value));
      }
    }
    value -= 31;
  }
  return a;
}

big_decimal to_big(s21_decimal a) {
  big_decimal b = {0};
  for (int i = 0; i < 3; i++) b.bits[i] = a.bits[i];
  b.bits[7] = a.bits[3];
  return b;
}

s21_decimal from_big(big_decimal a) {
  // Думаю, здесь будет округление ==================
  s21_decimal b = {0};
  for (int i = 0; i < 3; i++) b.bits[i] = a.bits[i];
  b.bits[3] = a.bits[7];
  return b;
}
// Сложить два числа одного порядка без учета знака
big_decimal big_plus_big(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int memory = 0, sum = 0;
  for (int i = 0; i < 32 * 7; i++) {
    sum = check_bit(value_1, i) + check_bit(value_2, i) + memory;
    memory = sum > 1 ? 1 : 0;
    set_bit(&result, i, sum % 2);
  }
  printf("%d +++\n", result.bits[0]);
  return result;
}
// Вычесть одно из второго, один порядок, без учета знака
big_decimal big_minus_big(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int debt = 0, sum = 0;
  for (int i = 0; i < 32 * 7; i++) {
    sum = check_bit(value_1, i) - check_bit(value_2, i) - debt;
    debt = sum < 0 ? 1 : 0;
    set_bit(&result, i, sum % 2);
  }
  return result;
}

// Умножение на 10
big_decimal big_x10(big_decimal value) {
  return big_plus_big(shift_big_decimal(value, 3, "L"),
                      shift_big_decimal(value, 1, "L"));
}
// Приведение к одинаковому порядку
void normalization(big_decimal *value_1, big_decimal *value_2) {
  int delta = get_scale(value_1->bits[7]) - get_scale(value_2->bits[7]);
  if (delta > 0) {
    set_scale(value_2->bits[7], get_scale(value_1->bits[7]));
    while (delta-- > 0) *value_2 = big_x10(*value_2);
  }
  if (delta < 0) {
    set_scale(value_1->bits[7], get_scale(value_2->bits[7]));
    while (delta++ < 0) *value_1 = big_x10(*value_1);
  }
}

// void print_decimal(s21_decimal a){
// }

// Проверка на бесконечность или переполнение