// E11 ДЗ 4
// Отсортировать по последней цифре
// Считать массив из 10 элементов и отсортировать его по последней цифре. 

// Данные на входе: 10 целых чисел через пробел 
// Этот же массив отсортированный по последней цифре

#include <stdio.h>
#include <inttypes.h>

const uint32_t ARRAY_SIZE = 10;

uint8_t last_digit(int32_t n);
void swap(int32_t* a, int32_t* b);
void bubble_sort_by_last_digit(int32_t array[], uint32_t size);

int main(void)
{
    int32_t input_array[ARRAY_SIZE];
    for (uint32_t i = 0; i < ARRAY_SIZE; ++i) {
        scanf("%d", &input_array[i]);
    }
    bubble_sort_by_last_digit(input_array, ARRAY_SIZE);
    for (uint32_t i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", input_array[i]);
    }
    putchar('\n');

    return 0;    
}

uint8_t last_digit(int32_t n)
{
    if (n < 0) {
        n = -n;
    }
    return n % 10;
}

void swap(int32_t* a, int32_t* b)
{
    int32_t tmp = *b;
    *b = *a;
    *a = tmp;
}

void bubble_sort_by_last_digit(int32_t array[], uint32_t size)
{
    uint8_t no_swap;
    for(uint32_t i = 0; i < size; ++i) {
        no_swap = 1;
        for(uint32_t j = size - 1; j > i; --j) {
            if(last_digit(array[j-1]) > last_digit(array[j]))
            {
                swap(&array[j], &array[j-1]);
                no_swap = 0;
            }
        }
        if (no_swap) {
            break;
        }
    }
}