// E20 ДЗ *
// Переставить цифры
// Переставить цифры в числе так, чтобы получилось максимальное число. 
// Данные на входе: Одно целое не отрицательное число 
// Данные на выходе: Целое неотрицательное число

#include <stdio.h>
#include <inttypes.h>

enum {
    MAX_NUMBER_LENGTH = 10
};

void decimal_digits(uint32_t number, uint8_t digits[], uint8_t* length);
void swap(uint8_t* a, uint8_t* b);
void bubble_sort_descending(uint8_t array[], uint32_t size);
void print_number(uint8_t digits[], uint8_t length);

int main(void)
{
    uint32_t n;
    scanf("%u", &n);
    uint8_t digits[MAX_NUMBER_LENGTH];
    uint8_t number_length;
    decimal_digits(n, digits, &number_length);
    bubble_sort_descending(digits, number_length);
    print_number(digits, number_length);

    return 0;    
}


void decimal_digits(uint32_t number, uint8_t digits[], uint8_t* length)
{
    uint8_t pos = 0;
    while(number > 0) {
        digits[pos++] = number % 10;
        number /= 10;
    }
    *length = pos;
}

void swap(uint8_t* a, uint8_t* b)
{
    int32_t tmp = *b;
    *b = *a;
    *a = tmp;
}

void bubble_sort_descending(uint8_t array[], uint32_t size)
{
    uint8_t no_swap;
    for(uint32_t i = 0; i < size; ++i) {
        no_swap = 1;
        for(uint32_t j = size - 1; j > i; --j) {
            if(array[j-1] < array[j])
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

void print_number(uint8_t digits[], uint8_t length)
{
    for(uint32_t i = 0; i < length; ++i) {
        printf("%hhu", digits[i]);
    }
    putchar('\n');
}