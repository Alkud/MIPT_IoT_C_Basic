// E16 Д3 6
// Чаще других
// Дан массив из 10 элементов. Определить, какое число в массиве встречается чаще всего. Гарантируется, что такое число ровно 1. 

// Данные на входе: 10 целых числе через пробел 
// Данные на выходе: Одно число, которое встречается чаще других.

#include <stdio.h>
#include <inttypes.h>

const uint32_t ARRAY_SIZE = 10;

void swap(int32_t* a, int32_t* b);
void bubble_sort(int32_t array[], uint32_t size);
int32_t most_frequent_item(int32_t array[], uint32_t size);

int main(void)
{
    int32_t input_array[ARRAY_SIZE];
    for (uint32_t i = 0; i < ARRAY_SIZE; ++i) {
        scanf("%d", &input_array[i]);
    }
    printf("%d\n", most_frequent_item(input_array, ARRAY_SIZE));

    return 0;    
}


void swap(int32_t* a, int32_t* b)
{
    int32_t tmp = *b;
    *b = *a;
    *a = tmp;
}

void bubble_sort(int32_t array[], uint32_t size)
{
    uint8_t no_swap;
    for(uint32_t i = 0; i < size; ++i) {
        no_swap = 1;
        for(uint32_t j = size - 1; j > i; --j) {
            if(array[j-1] > array[j])
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


int32_t most_frequent_item(int32_t array[], uint32_t size)
{
    bubble_sort(array, size);
    uint32_t max_count = 0;
    int32_t res;
    for(uint32_t i = 0; i < size;) {
        uint32_t count = 1;
        uint32_t j = i++;
        while(i < size && array[j] == array[i]) {
            ++count;
            ++i;
        }
        if (count > max_count) {
            max_count = count;
            res = array[j];
        }
    }
    return res;
}
