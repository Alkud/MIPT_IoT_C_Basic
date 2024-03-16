//  D3 Практика 1
//  В обратном порядке
//  Дано целое неотрицательное число N. Выведите все его цифры по одной, в обратном порядке, разделяя их пробелами или новыми строками. 
//  Данные на входе: Одно неотрицательное целое число 
//  Данные на выходе: Последовательность цифр введенного числа в обратном порядке через пробел 

#include <stdio.h>
#include <inttypes.h>


void print_in_reverse_order(uint32_t n);


int main(void)
{
    uint32_t a;
    scanf("%u", &a);
    print_in_reverse_order(a);

    return 0;
}


void print_in_reverse_order(uint32_t n)
{
    if (n < 10) {
        printf("%hhu\n", n);
    } else {
        printf("%hhu ", n % 10);
        print_in_reverse_order(n / 10);
    }
}
