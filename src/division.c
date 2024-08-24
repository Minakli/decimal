#include "s21_decimal.h"
#include <stdio.h>
#include <stdbool.h>

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res = OK;
    value_1.bits[0] = 100000;
    value_1.bits[1] = 100;
    value_1.bits[2] = 1000000;
    value_1.bits[3] = 199999999;
    // int a = 0b10000011;
    // unsigned int b = 0b00000000;
    // print_32_bit(a);
    // print_32_bit(~a);
    // print_decimal(value_1);
    // print_32_binary(value_1.bits[0]);
    // printf("value_1.bits[0]: %d", value_1.bits[0]);
    value_1.bits[0] = value_1.bits[0] >> 5;
    value_1.bits[0] = value_1.bits[0] * 32;
    // set_bit(&value_1, 0, false);
    // set_bit(&value_1, 63, true);
    // printf("\n");
    // print_decimal(value_1);
    // print_32_binary(value_1.bits[0]);
    // printf("value_1.bits[0]: %d", value_1.bits[0]);
    // printf("\n");
    // printf("check: %d\n", check_bit(value_1, 0) ? 1 : 0);
    if(0) {
        res = TOO_BIG;
    } else if(0) {
        res = TOO_LITTLE;
    } else if(0) {
        res = DIV_BY_ZERO;
    }
    return res;
}