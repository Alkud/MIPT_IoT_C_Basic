// E18
// Кратность прежде всего
// В диапазоне натуральных чисел от 2 до N определить, сколько из них кратны любому из чисел в диапазоне от 2 до 9. 

// Данные на входе: Одно целое число N большее 2 и не превосходящее 10000 
// Данные на выходе: Все числа от 2 до 9 в формате: 2 количество чисел кратных 2
//                                                  3 количество чисел кратных 3
//                                                  4 количество чисел кратных 4
//                                                  5 количество чисел кратных 5
//                                                  6 количество чисел кратных 6
//                                                  7 количество чисел кратных 7
//                                                  8 количество чисел кратных 8
//                                                  9 количество чисел кратных 9


#include <stdio.h>
#include <inttypes.h>

enum {
    MIN_DIVISOR = 2U,
    MAX_DIVISOR = 9U
};

void multiple_counter(uint32_t number, uint32_t min_divisor, uint32_t max_divisor, uint32_t counts[]);
void print_multiple_counts(uint32_t counts[], uint32_t min_divisor, uint32_t max_divisor);


int main(void)
{
    uint32_t n;
    scanf("%u", &n);
    uint32_t num_divisors = MAX_DIVISOR - MIN_DIVISOR + 1;
    uint32_t multiple_counts[num_divisors];
    multiple_counter(n, MIN_DIVISOR, MAX_DIVISOR, multiple_counts);
    print_multiple_counts(multiple_counts, MIN_DIVISOR, MAX_DIVISOR);

    return 0;
}


void multiple_counter(uint32_t number, uint32_t min_divisor, uint32_t max_divisor, uint32_t counts[])
{
    for(uint32_t div = min_divisor; div <= max_divisor; ++div ) {
        counts[div - min_divisor] = 0;
        for(uint32_t factor = 1; div * factor <= number; ++factor) {
            counts[div - min_divisor] += 1;
        }
    }
}

void print_multiple_counts(uint32_t counts[], uint32_t min_divisor, uint32_t max_divisor)
{
    for (uint32_t i = min_divisor; i <= max_divisor; ++i) {
        printf("%u %d\n", i, counts[i - min_divisor]);
    }
}