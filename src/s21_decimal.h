#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_
#include <stdbool.h>

/// errors
#define OK 0
#define CONVERT_ERROR 1

#define TOO_BIG 1
#define TOO_LITTLE 2
#define DIV_BY_ZERO 3

#define FALSE 0
#define TRUE 1

typedef struct {
  int bits[4];
} s21_decimal;

// Из int
int s21_from_int_to_decimal(int src, s21_decimal *dst);
// Из float
int s21_from_float_to_decimal(float src, s21_decimal *dst);
// В int
int s21_from_decimal_to_int(s21_decimal src, int *dst);
// В float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Сложение
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вычитание
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Деление
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Меньше
int s21_is_less(s21_decimal, s21_decimal);
// Меньше или равно
int s21_is_less_or_equal(s21_decimal, s21_decimal);
// Больше
int s21_is_greater(s21_decimal, s21_decimal);
// Больше или равно
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
// Равно
int s21_is_equal(s21_decimal, s21_decimal);
// Не равно
int s21_is_not_equal(s21_decimal, s21_decimal);



// Печать одного числа в двоичном виде
void print_32_bit(int a);
// Печать децимел в двоичном виде
void print_decimal(s21_decimal a);
// Проверка указанного бита
bool check_bit(s21_decimal a, int num);
// Установка указанного бита указанным значением
void set_bit(s21_decimal *a, int num, bool choice);
#endif  //  SRC_S21_DECIMAL_H_