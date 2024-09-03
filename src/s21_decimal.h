#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_
#include <stdbool.h>
#include <stdio.h>

/// errors
#define OK 0
#define CONVERT_ERROR 1

#define TOO_BIG 1
#define TOO_LITTLE 2
#define DIV_BY_ZERO 3

#define FALSE 0
#define TRUE 1

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} big_decimal;

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

// Печать одного числа в двоичном виде (УБРАТЬ!)
void print_32_binary(int a);
// Печать децимел в двоичном виде (УБРАТЬ!)
void print_binary(big_decimal a);
// Проверка указанного бита
bool check_bit(big_decimal a, int num);
// Установка указанного бита указанным значением
void set_bit(big_decimal *a, int num, int choice);
// Печать децимел в десятичном виде (УБРАТЬ!)
void print_decimal(s21_decimal a);
// Проверить знак
bool check_sign(s21_decimal a);
// Установить знак
void set_sign(s21_decimal *a, bool choice);
// Получить разряд
int get_scale(big_decimal a);
// Установить разряд
void set_scale(big_decimal *a, int num);
// Проверка на ноль
bool is_not_null(big_decimal a);
// Сдвиг по количеству и направлению (L or R)
big_decimal shift_big_decimal(big_decimal a, int value, char vector);
// Перевод в биг децимел
big_decimal to_big(s21_decimal a);
// Перевод из биг в децимел
s21_decimal from_big(big_decimal a);
#endif  //  SRC_S21_DECIMAL_H_