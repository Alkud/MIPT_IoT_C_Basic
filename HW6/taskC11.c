// C11 ДЗ
// НОД
// Составить функцию, которая определяет наибольший общий делитель двух натуральных и привести пример ее использования.
// int nod(int a, int b)
// Данные на входе: Два целых положительных числа
// Данные на выходе: Одно целое число - наибольший общий делитель.

#include <stdio.h>
#include <inttypes.h>


uint32_t nod(uint32_t a, uint32_t b);

int main(void)
{
    uint32_t a, b;
    scanf("%u%u", &a, &b);
    printf("%u\n", nod(a, b));

    return 0;
}

uint32_t nod(uint32_t a, uint32_t b)
{
    while (a != b) {
        if  (a > b) {
            if (a % b == 0) {
                return b;
            }
            a %= b;
            if (a == 1) {
                return 1;
            }
        } else {
            if (b % a == 0) {
                return a;
            }
            b %= a;
            if (b == 1) {
                return 1;
            }
        }
    }
    return a;
}
