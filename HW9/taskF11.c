// F11 Практ 3
// Сумма минимальна
// Написать функцию и программу, демонстрирующую работу данной функции.
// Дан целочисленный массив из 30 элементов. Элементы массива могут принимать произвольные целые значения помещающиеся в int.
// Необходимо создать функцию, которая находит и выводит в порядке возрастания номера двух элементов массива, сумма которых минимальна. 

#include <stdio.h>


enum{
    ARRAY_SIZE = 30
};


void print_min_sum_items(int size, int a[]);
void scan_array(int n, int a[]);


int main(void)
{
    int input_array[ARRAY_SIZE];
    scan_array(ARRAY_SIZE, input_array);
    print_min_sum_items(ARRAY_SIZE, input_array);

    return 0;
}


void print_min_sum_items(int size, int a[])
{
    int min = a[0];
    int min_pos = 0;
    int quasi_min = a[1];
    int quasi_min_pos = 1;
    for (int i = 2; i < size; ++i) {
        if (a[i] < min) {
            quasi_min = min;
            quasi_min_pos = min_pos;
            min = a[i];
            min_pos = i;
        } else if (a[i] < quasi_min) {
            quasi_min = a[i];
            quasi_min_pos = i;
        }
    }
    if (min_pos < quasi_min_pos) {
        printf("%d %d\n", min_pos, quasi_min_pos);
    } else {
        printf("%d %d\n", quasi_min_pos, min_pos);
    }
}

void scan_array(int n, int a[])
{
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
}
