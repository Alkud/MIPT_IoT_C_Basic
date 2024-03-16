// D4 ДЗ 1
// В прямом порядке
// Дано натуральное число N. Выведите все его цифры по одной, в прямом порядке, разделяя их пробелами или новыми строками. Необходимо реализовать рекурсивную функцию.
// void print_num(int num)
// Данные на входе: Одно целое неотрицательное число 
// Данные на выходе: Все цифры числа через пробел в прямом порядке. 


#include <stdio.h>
#include <inttypes.h>


void print_num(uint32_t num);


int main(void)
{
    uint32_t a;
    scanf("%u", &a);
    print_num(a);
    putchar('\n');

    return 0;
}

void print_num(uint32_t num)
{
    if (num < 10) {
        printf("%hhu ", num % 10);
    } else {
        print_num(num / 10);
        printf("%hhu ", num % 10);
    }
}