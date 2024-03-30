// F2 ДЗ 2
// Четные в начало
// Написать функцию и программу, демонстрирующую работу данной функции, которая ставит в начало массива все четные элементы, а в конец – все нечетные.
// Не нарушайте порядок следования чисел между собой. Строго согласно прототипу:
// void sort_even_odd(int n, int a[])
// Данные на входе: Функция принимает на вход целые числа 
// Данные на выходе: Отсортированный исходный массив

#include <stdio.h>


void sort_even_odd(int n, int a[]);
void scan_array(int n, int a[]);
void print_array(int n, int a[]);


int main(void)
{
    int n;
    scanf("%d", &n);
    int input_array[n];
    scan_array(n, input_array);
    sort_even_odd(n, input_array);
    print_array(n, input_array);

    return 0;
}


void sort_even_odd(int n, int a[])
{
    int even_index = 0;
    int odd_index = n - 1;
    int tmp_array[n];
    for(int i = 0; i < n; ++i) {
        if (a[i] % 2 == 0) {
            tmp_array[even_index] = a[i];
            ++even_index;
        }
        if (a[n - 1 - i] % 2 != 0) {
            tmp_array[odd_index] = a[n - 1 - i];
            --odd_index;
        }
    }
    for(int i = 0; i < n; ++i) {
        a[i] = tmp_array[i];
    }    
}

void scan_array(int n, int a[])
{
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
}

void print_array(int n, int a[])
{
    for(int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    putchar('\n');
}