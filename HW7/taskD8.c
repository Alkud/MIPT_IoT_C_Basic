// D8 ДЗ 2
// От A до B
// Составить рекурсивную функцию, Выведите все числа от A до B включительно, в порядке возрастания, если A < B, или в порядке убывания в противном случае.
// Данные на входе: Два целых числа через пробел.
// Данные на выходе: Последовательность целых чисел.

#include <stdio.h>
#include <inttypes.h>

void print_sequence(int32_t a, int32_t b);

int main(void)
{
    int32_t m, n;
    scanf("%d%d", &m, &n);
    print_sequence(m, n);

    return 0;
}

void print_sequence(int32_t a, int32_t b)
{
    if (a == b) {
        printf("%d\n", a);
    } else if (a < b) {
        printf("%d ", a++);
        print_sequence(a, b);
    } else {
        printf("%d ", a--);
        print_sequence(a, b);
    }
}