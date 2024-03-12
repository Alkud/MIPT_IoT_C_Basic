// C5 ДЗ
// Сумма от 1 до N
// Составить функцию, которая определяет сумму всех чисел от 1 до N и привести пример ее использования.
// Данные на входе: Одно целое положительное число N
// Данные на выходе: Целое число - сумма чисел от 1 до N

#include <stdio.h>
#include <inttypes.h>


uint64_t sum_of_digits(uint32_t a);

int main(void)
{
    uint32_t n;
    scanf("%u", &n);
    printf("%lu\n", sum_of_digits(n));

    return 0;
}

uint64_t sum_of_digits(uint32_t a)
{
    uint64_t sum = 0U;
    for(; a >= 1; --a) {
        sum += a;
    }
    return sum;
}

