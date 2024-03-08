//B4 Урок 5 ДЗ 2
//Ровно три цифры
//Ввести целое число и определить, верно ли, что в нём ровно 3 цифры.
//Данные на входе: Целое положительное число
//Данные на выходе:	Одно слово: YES или NO

#include <stdio.h>
#include <inttypes.h>


int main()
{
    uint32_t n;
    scanf("%u", &n);
    uint8_t digitCount = 0U;
    while(digitCount < 3 && n > 0) {
        digitCount += 1;
        n /= 10;
    }
    printf((digitCount == 3 && n == 0)? "YES\n": "NO\n");

    return 0;
}
