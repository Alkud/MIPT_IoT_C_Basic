// F8 Практ 2
// Пропущенное число
// Написать функцию и программу, демонстрирующую работу данной функции.
// В последовательности записаны целые числа от M до N ( M меньше N, M больше или равно 1) в произвольном порядке, но одно из чисел пропущено
// (остальные встречаются ровно по одному разу). N не превосходит 1000. Последовательность заканчивается числом 0. Определить пропущенное число. 
// Данные на входе: Последовательность целых чисел от M до N. M, N не превосходит 1000. 
// Данные на выходе: Одно целое число


#include <stdio.h>

enum{
    MAX_ARRAY_SIZE = 1000
};


int missing_item(int size, int a[]);
int scan_array(int a[]);


int main(void)
{
    int input_array[MAX_ARRAY_SIZE];
    int n = scan_array(input_array);
    printf("%d\n", missing_item(n, input_array));

    return 0;
}


int missing_item(int size, int a[])
{
    /* SORTING */
    // for(int i = 0; i < size; ++i) {
    //     int j;
    //     for(j = size - 1; j > i; --j) {
    //         if(a[j-1] > a[j])
    //         {
    //             int tmp = a[j-1];
    //             a[j - 1] = a[j];
    //             a[j] = tmp;
    //         }
    //     }
    //     if (i > 0 && a[i - 1] + 1 != a[i]) {
    //         return a[i - 1] + 1;
    //     }
    // }  
    // return 0;
    /* SUM OF PROGRESSION */
    int min = a[0];
    int max = a[0];
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += a[i];
        if (a[i] < min) {
            min = a[i];
        }
        if (a[i] > max) {
            max = a[i];
        }
    }
    float expected_sum = 0.5F * (max + min) * (max - min + 1);
    return (int)expected_sum - sum;
}

int scan_array(int a[])
{
    int i = 0;
    int n;
    while(i < MAX_ARRAY_SIZE) {
        scanf("%d", &n);
        if (n == 0) {
            break;
        }
        a[i] = n;
        ++i;
    }
    return i;
}
