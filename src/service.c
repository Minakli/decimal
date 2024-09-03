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
  a->bits[num / 32] =
      choice ? a->bits[0] | (1 << (num % 32)) : a->bits[0] & (~1 << (num % 32));
}

bool check_sign(s21_decimal a) { return ((a.bits[3] >> 31) & 1) ? true : false; }

void set_sign(s21_decimal *a, bool choice) {
  a->bits[3] = (choice ? (a->bits[3] >> 31) | 1 : (a->bits[3] >> 31) & ~1) << 31;
}

int get_scale(big_decimal a) { return (a.bits[7] >> 16) & 255; }

void set_scale(big_decimal *a, int num) {
  a->bits[7] = (((a->bits[3] >> 16) & 0) | num) << 16;
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

big_decimal big_x10(big_decimal a) {
  // return big_decimal_add(shift_big_decimal(a, 3, 'L'),shift_big_decimal(a, 1,
  // 'L'), &res);
}

// void print_decimal(s21_decimal a){
// }

// Проверка на бесконечность или переполнение