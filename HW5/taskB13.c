//B13
//Количество четных и нечетных цифр
//Подсчитать количество четных и нечетных цифр числа.
//
//Данные на входе: Одно целое неотрицательное число.
//Данные на выходе:	Два числа через пробел. Количество четных и нечетных цифр в числе.

#include <stdio.h>
#include <inttypes.h>


int main() {
    uint32_t n;
    scanf("%u", &n);
    uint8_t evenCount = 0U;
    uint8_t oddCount = 0U;
    while(n > 0) {
        uint8_t digit = n % 10;
        if (digit % 2 == 0) {
            evenCount += 1;
        } else {
            oddCount += 1;
        }
        n /= 10;
    }
    printf("%hhu %hhu\n", evenCount, oddCount);

    return 0;
}