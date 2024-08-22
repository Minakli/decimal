#include "s21_decimal.h"
#include <stdio.h>
#include <stdbool.h>

void print_32_bit(int a) {
        int mask = 0b00000001;
        printf("-- ");
    for(int i = 31; i > -1; i--) {
        printf("%d", (a >> i) & mask);
    }
    printf("\n");
}

void print_decimal(s21_decimal a){
    for(int i = 0; i < 4; i++) {
        print_32_bit(a.bits[i]);
    }
}
bool check_bit(s21_decimal a, int num){
    bool res = false;
    int mask = 1;
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
    int mask = choice ? 1 : ~1;
    if(num < 32) {
        a->bits[0] = choice ? a->bits[0] | (mask << num): a->bits[0] & (mask << num);
    } else if(num < 64){
        a->bits[1] = choice ? a->bits[1] | (mask << (num - 32)): a->bits[1] & (mask << (num - 32));
    } else if(num < 96) {
        a->bits[2] = choice ? a->bits[2] | (mask << (num - 64)): a->bits[2] & (mask << (num - 64));
    } else if(num < 96) {
        a->bits[3] = choice ? a->bits[3] | (mask << (num - 96)): a->bits[3] & (mask << (num - 96));
    }
}