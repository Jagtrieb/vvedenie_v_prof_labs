#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define ACCURACY 1000000000ULL

typedef struct timespec NewTime;

typedef struct {
    int sign;
    unsigned long long whole;
    unsigned long long fractional;
} BigFloat;

int get_unsigned_long_len(unsigned long long x){
    if (x == 0) return 1;
    int res = 0;
    while (x != 0){
        res++;
        x /= 10;
    }
    return res;
}

void align_fractions(long long* a, long long* b){
    int x = *a, xCounter = get_unsigned_long_len(x);
    int y = *b, yCounter = get_unsigned_long_len(y);
    
    int n = abs(xCounter - yCounter);
    if (xCounter > yCounter) *b *= pow(10, n);
    else *a *= pow(10, n);
}

bool is_abs_greater(BigFloat A, BigFloat B){
    if (A.whole != B.whole){
        if (A.whole > B.whole) return true;
        else return false;
    }
    if (A.fractional != B.fractional){
        if (A.fractional > B.fractional) return true;
    }
    return false;
}

BigFloat addBFs(BigFloat A, BigFloat B){
    long long x_whole, x_fractional;
    int x_sign = 1;

    long long A_f_copy = A.fractional;
    long long B_f_copy = B.fractional;
    align_fractions(&A_f_copy, &B_f_copy);
    int del = pow(10, get_unsigned_long_len(A_f_copy));

    if ((A.sign < 0) ^ (B.sign < 0)){
        if (is_abs_greater(A, B)){
            x_whole = A.whole - B.whole;
            x_fractional = A_f_copy - B_f_copy;
        }
        else {
            x_whole = B.whole - A.whole;
            x_fractional = B_f_copy - A_f_copy;
        }
        
        if (x_fractional < 0){
            x_fractional += del;
            x_whole--;
        } 
        x_sign = is_abs_greater(A, B) ? A.sign : B.sign;
    }
    else {
        x_whole = A.whole + B.whole;
        x_fractional = (A_f_copy + B_f_copy) % del;
        x_whole += (A_f_copy + B_f_copy) / del;
        x_sign = A.sign;
    }

    //printf("%lld %llu %llu\n", x_whole, A.whole, B.whole);

    BigFloat x = {x_sign, x_whole, x_fractional};
    return x;
}

BigFloat subBFs(BigFloat A, BigFloat B){
    B.sign = -1;
    return addBFs(A, B);
}

BigFloat mulBFs(BigFloat A, BigFloat B){
    unsigned long long x_whole = 0, x_fractional = 0;
    int x_sign = A.sign * B.sign;
    int A_f_len = get_unsigned_long_len(A.fractional);
    int B_f_len = get_unsigned_long_len(B.fractional);
    unsigned long long A_mul = A.whole * pow(10, A_f_len) + A.fractional;
    unsigned long long B_mul = B.whole * pow(10, B_f_len) + B.fractional;

    __uint128_t total_product = (__uint128_t) A_mul * (__uint128_t) B_mul;
    unsigned long long separator = pow(10, (A_f_len + B_f_len));
    x_whole = total_product / separator;
    x_fractional = total_product % separator;

    BigFloat x = {x_sign, x_whole, x_fractional};
    return x;
}

BigFloat divBFs(BigFloat A, BigFloat B){
    unsigned long long x_whole = 0, x_fractional = 0;
    int x_sign = A.sign * B.sign;
    int A_f_len = get_unsigned_long_len(A.fractional);
    int B_f_len = get_unsigned_long_len(B.fractional);
    unsigned long long A_mul = A.whole * pow(10, A_f_len) + A.fractional;
    unsigned long long B_mul = B.whole * pow(10, B_f_len) + B.fractional;

    __uint128_t mega_A = (__uint128_t)A_mul * ACCURACY;
    unsigned long long total_product = mega_A / B_mul;
    x_whole = total_product / ACCURACY;
    x_fractional = total_product % ACCURACY;

    BigFloat x = {x_sign, x_whole, x_fractional};
    return x;  
}

BigFloat powBFs(BigFloat A, int n){
    if (n < 0){
        BigFloat tmp = powBFs(A, -n);
        BigFloat upper = {1, 1, 0};
        return divBFs(upper, tmp);
    }
    BigFloat x = A; 
    for (int i = 0; i < n - 1; i++){
        x = mulBFs(x, A);
    }
    return x;
}

void print_BF(BigFloat A){
    if (A.sign == -1) printf("-");
    printf("%llu.%llu", A.whole, A.fractional);
}

void scan_BF(BigFloat* A){
    int x_sign = 1;
    unsigned long long x_whole = 0, x_fractional = 0;
    bool sep_flag = false;

    char input[100];
    scanf("%s", input);
    int n = strlen(input);
    int start_value = 0;
    if (input[0] == '-'){
        start_value = 1;
        x_sign = -1;
    }
    for (int i = start_value; i < n; i++){
        if (input[i] != '.'){
            if (sep_flag) x_fractional = 10 * x_fractional + (input[i] - '0');
            else x_whole = 10 * x_whole + (input[i] - '0');
        }
        else sep_flag = true;
    }

    A -> sign = x_sign;
    A -> whole = x_whole;
    A -> fractional = x_fractional;
}

uint64_t get_millisecs(){
    NewTime ct;
    timespec_get(&ct, TIME_UTC);
    uint64_t res = (uint64_t)ct.tv_sec * 1000 + (uint64_t)ct.tv_nsec / 1000000;
    return res;
}

int main(){
    uint64_t start, finish;

    BigFloat A;
    BigFloat B;
    int n;
    BigFloat x;
    printf("Введите число A: ");
    scan_BF(&A);
    printf("Введите число B: ");
    scan_BF(&B);
    printf("Введите N для последующего возведения числа A в степень N: ");
    scanf("%d", &n);
    printf("Введённые числа:\nA = ");
    print_BF(A);
    printf("\tB = ");
    print_BF(B);
    printf("\tN = %d", n);

    printf("\n\n===== Математические вычисления с A и B =====\n");
    start = get_millisecs();
    printf("A + B = ");
    print_BF(addBFs(A, B));

    printf("\nA - B = ");
    print_BF(subBFs(A, B));

    printf("\nA * B = ");
    print_BF(mulBFs(A, B));
    
    printf("\nA / B = ");
    print_BF(divBFs(A, B));

    printf("\nA ^ %d = ", n);
    print_BF(powBFs(A, n));
    finish = get_millisecs();
    printf("\n=============================================\n\n");
    
    printf("Время работы программы: %luмс.\n", (unsigned long)(finish - start));
    return 0;
}