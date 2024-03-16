// D16 Практик 3
// Точная степень двойки
// Написать логическую рекурсивную функцию и используя ее определить является ли введенное натуральное число точной степенью двойки.
// int is2pow(int n)
// Данные на входе: Одно натуральное число. 
// Данные на выходе: YES или NO

#include <stdio.h>
#include <inttypes.h>

uint8_t is2pow(uint32_t n);

int main(void)
{
    uint32_t a;
    scanf("%u", &a);
    printf(is2pow(a) ? "YES\n" : "NO\n");

    return 0;
}

uint8_t is2pow(uint32_t n)
{
    if (n == 1 || n == 2) {
        return 1;
    } else if (n == 0 || n % 2 != 0) {
        return 0;
    } else {
        return is2pow(n / 2);
    }
}