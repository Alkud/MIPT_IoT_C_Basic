// E1 ДЗ 1
// Среднее арифметическое чисел
// Ввести c клавиатуры массив из 5 элементов, найти среднее арифметическое всех элементов массива. 

// Данные на входе: 5 целых ненулевых чисел через пробел 
// Данные на выходе: Одно число в формате "%.3f"

#include <stdio.h>
#include <inttypes.h>

const uint32_t ARRAY_SIZE = 5;

float mean(int32_t array[], uint32_t size);


int main(void)
{
    int32_t input_array[ARRAY_SIZE];
    for (uint32_t i = 0; i < ARRAY_SIZE; ++i) {
        scanf("%d", &input_array[i]);
    }
    printf("%.3f\n", mean(input_array, ARRAY_SIZE));

    return 0;
}


float mean(int32_t array[], uint32_t size)
{
    float sum = 0.0;
    for (uint32_t i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum / size;
}