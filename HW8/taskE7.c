// E7 Практик 2
// Инверсия половинок
// Считать массив из 10 элементов и выполнить инверсию отдельно для 1-ой и 2-ой половин массива. Необходимо изменить считанный массив и напечатать его одним циклом.
// Данные на входе: 10 целых элементов массива через пробел. 
// Данные на выходе: 10 целых элементов массива через пробел. 

#include <stdio.h>
#include <inttypes.h>

const uint32_t ARRAY_SIZE = 10;

void swap(int32_t* a, int32_t* b);
void reverse_and_print(int32_t* array, uint32_t size);


int main(void)
{
    int32_t input_array[ARRAY_SIZE];
    for (uint32_t i = 0; i < ARRAY_SIZE; ++i) {
        scanf("%d", &input_array[i]);
    }
    reverse_and_print(&input_array[0], ARRAY_SIZE / 2);
    reverse_and_print(&input_array[ARRAY_SIZE / 2], ARRAY_SIZE / 2);
    putchar('\n');

    return 0;    
}


void swap(int32_t* a, int32_t* b)
{
    int32_t tmp = *b;
    *b = *a;
    *a = tmp;
}

void reverse_and_print(int32_t* array, uint32_t size)
{
    for(uint32_t i = 0; i < size; ++i) {
        if (i < size / 2) {
            swap(&array[i], &array[size - 1 - i]);
        }
        printf("%d ", array[i]);
    }
}