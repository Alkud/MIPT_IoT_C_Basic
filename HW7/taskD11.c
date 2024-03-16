// D11 ДЗ 3
// Количество 1
// Дано натуральное число N. Посчитать количество «1» в двоичной записи числа. 
// Данные на входе: Натуральное число
// Данные на выходе: Целое число - количество единиц в двоичной записи числа.

#include <stdio.h>
#include <inttypes.h>

uint32_t num_binary_ones(uint32_t num);

int main(void)
{
    uint32_t n;
    scanf("%u", &n);
    printf("%u\n", num_binary_ones(n));

    return 0;
}

uint32_t num_binary_ones(uint32_t num)
{
    uint32_t res = 0U;
    if (num < 2) {
        res = num;
    } else {
        res = num % 2 + num_binary_ones(num / 2);
    }
    return res;
}