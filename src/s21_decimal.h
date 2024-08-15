#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

/// errors
#define OK 0
#define CONVERT_ERROR 1

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

#endif  //  SRC_S21_DECIMAL_H_