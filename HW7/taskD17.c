// D17 ДЗ 5 ДЗ*
// Функция Аккермана
// Функция Аккермана определяется рекурсивно для неотрицательных целых чисел m и n следующим образом:
// A(0,m)     = m+1
// A(n+1,0)   = A(n,1)
// A(n+1,m+1) = A(n,A(n+1,m))
// Реализуйте данную функцию по прототипу
// int akkerman(int m, int n)
// Данные на входе: Даны неотрицательные целые числа m и n 
// Данные на выходе: Одно целое число 

#include <stdio.h>
#include <inttypes.h>

uint64_t akkerman(uint64_t m, uint64_t n);

int main(void)
{
    uint64_t a, b;
    scanf("%lu%lu", &a, &b);
    printf("%lu\n", akkerman(a, b));

    return 0;
}

uint64_t akkerman(uint64_t m, uint64_t n)
{
    if (m == 0) {
        return n + 1; 
    }
    if (n == 0) {
        return akkerman(m - 1, 1);
    }
    return akkerman(m - 1, akkerman(m, n - 1));
}