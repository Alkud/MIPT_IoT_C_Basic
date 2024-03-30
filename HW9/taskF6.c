// F6 ДЗ 4
// Два одинаковых
// Написать функцию и программу, демонстрирующую работу данной функции, которая определяет, верно ли,
/// что среди элементов массива есть два одинаковых.
// Если ответ «да», функция возвращает 1; если ответ «нет», то 0. Строго согласно прототипу:
// int is_two_same(int size, int a[]);
// Данные на входе: Массив из целых чисел 
// Данные на выходе: Функция возвращает 1 или 0 


#include <stdio.h>


int is_two_same(int size, int a[]);
void scan_array(int n, int a[]);


int main(void)
{
    int n;
    scanf("%d", &n);
    int input_array[n];
    scan_array(n, input_array);
    printf("%d\n", is_two_same(n, input_array));

    return 0;
}


int is_two_same(int size, int a[])
{
    int no_swap;
    for(int i = 0; i < size; ++i) {
        no_swap = 1;
        for(int j = size - 1; j > i; --j) {
            if (a[j] == a[j-1]) {
                return 1;
            }
            if(a[j-1] > a[j])
            {
                int tmp = a[j-1];
                a[j - 1] = a[j];
                a[j] = tmp;
                no_swap = 0;
            }
        }
        if (no_swap) {
            break;
        }
    }  
    return 0;
}

void scan_array(int n, int a[])
{
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
}