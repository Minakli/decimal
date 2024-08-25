#include "s21_decimal.h"
#include <stdio.h>
#include <stdbool.h>

void print_32_binary(int a) {
        unsigned mask = 0b00000001;
        printf("-- ");
    for(int i = 31; i > -1; i--) {
        printf("%d", (a >> i) & mask);
    }
    printf("\n");
}

void print_binary(s21_decimal a){
    for(int i = 0; i < 4; i++) {
        print_32_binary(a.bits[i]);
    }
}
bool check_bit(s21_decimal a, int num){
    bool res = false;
    unsigned mask = 1;
    if(num < 32) {
        res = (a.bits[0] >> num) & mask ? true : false;
    } else if(num < 64){
        res = (a.bits[1] >> num) & mask ? true : false;
    } else if(num < 96) {
        res = (a.bits[2] >> num) & mask ? true : false;
    }
    return res;
}
void set_bit(s21_decimal *a, int num, bool choice) {
    unsigned mask = choice ? 1 : ~1;
    if(num < 32) {
        a->bits[0] = choice ? a->bits[0] | (mask << num): a->bits[0] & (mask << num);
    } else if(num < 64){
        a->bits[1] = choice ? a->bits[1] | (mask << (num - 32)): a->bits[1] & (mask << (num - 32));
    } else if(num < 96) {
        a->bits[2] = choice ? a->bits[2] | (mask << (num - 64)): a->bits[2] & (mask << (num - 64));
    } 
    // else if(num < 128) {
    //     a->bits[3] = choice ? a->bits[3] | (mask << (num - 96)): a->bits[3] & (mask << (num - 96));
    // } 
}

bool check_sign(s21_decimal a){
    unsigned mask = 1;
    return (a.bits[3] & mask) ? true : false;
}

void set_sign(s21_decimal *a, bool choice){
    unsigned mask = choice ? 1: ~1;
    a->bits[3] = choice ? a->bits[3] | mask : a->bits[3] & mask;
}
int get_scale(s21_decimal a){
    unsigned mask = 255;
    return (a.bits[3] >> 8) & mask;
}

void set_scale(s21_decimal *a, int num){
    a->bits[3] = (((a->bits[3] >> 8)& 0) | num) << 8;
    // a->bits[3] = a->bits[3] >> 8;
    // a->bits[3] = a->bits[3] & 0;
    // a->bits[3] = a->bits[3] | num;
    // a->bits[3] = a->bits[3] << 8;
}

bool is_not_null(s21_decimal a){
    return (a.bits[0] == a.bits[1] == a.bits[2] == 0) ? false : true;
}

big_decimal shift_big_decimal(big_decimal a, int value, char vector){
    unsigned memory = 0, tmp = 0;
    printf("value: %d\n", value);
    while(value > 0) {
    if(vector == 'L'){ 
    for(int i = 0; i < 7; i++){
        tmp = a.bits[i];
        a.bits[i] = a.bits[i] << (value > 31 ? 31: value);
        a.bits[i] |= memory;
        memory = tmp >> (32 - (value > 31 ? 31: value));
        }
    } else if(vector == 'R'){
        for(int i = 6; i >= 0; i++){
        tmp = a.bits[i];
        a.bits[i] = a.bits[i] >> value > 31 ? 31: value;
        a.bits[i] |= memory;
        memory = tmp << (32 - value > 31 ? 31: value);
        }
    }
    value -= 31;
    } 
    return a;
}

big_decimal big_x10(big_decimal a){
    // return big_decimal_add(shift_big_decimal(a, 3, 'L'),shift_big_decimal(a, 1, 'L'), &res);
}



// void print_decimal(s21_decimal a){
// }

// Биг децимел
// Шифт 
// Биг Умножить на 10