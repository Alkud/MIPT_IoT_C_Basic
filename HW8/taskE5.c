// E5
// Сумма положительных элементов
// Считать массив из 10 элементов и подсчитать сумму положительных элементов массива. 

// Данные на входе: 10 целых чисел через пробел 
// Данные на выходе: Одно целое число - сумма положительных элементов массива 

#include <stdio.h>
#include <inttypes.h>

const uint32_t ARRAY_SIZE = 10;

int64_t positive_sum(int32_t array[], uint32_t size);


int main(void)
{
    int32_t input_array[ARRAY_SIZE];
    for (uint32_t i = 0; i < ARRAY_SIZE; ++i) {
        scanf("%d", &input_array[i]);
    }
    printf("%ld\n", positive_sum(input_array, ARRAY_SIZE));

    return 0;
}


int64_t positive_sum(int32_t array[], uint32_t size)
{
    int64_t sum = 0;
    for (uint32_t i = 0; i < size; ++i) {
        if (array[i] > 0) {
            sum += array[i];
        }
    }
    return sum;
}