//B8
//Ровно одна цифра 9
//Ввести целое число и определить, верно ли, что в нём ровно одна цифра «9».
//Данные на входе: Одно целое число
//Данные на выходе:	Одно слово: YES или NO

#include <stdio.h>
#include <inttypes.h>


int main() {
    int32_t n;
    scanf("%d", &n);
    uint8_t nineCount = 0U;
    while(n != 0 && nineCount <= 1) {
        if (n % 10 == 9 || n % 10 == -9) {
            nineCount += 1;
        }
        n /= 10;
    }
    printf((nineCount == 1 && n == 0) ? "YES\n" : "NO\n");

    return 0;
}