//B9 Урок 5 ДЗ 3
//Все цифры четные
//Ввести целое число и определить, верно ли, что все его цифры четные.
//Данные на входе: Одно целое число
//Данные на выходе:	YES или NO

#include <stdio.h>
#include <inttypes.h>


int main() {
    int32_t n;
    scanf("%d", &n);
    while (n != 0 ) {
        if ((n % 10) % 2 != 0) {
            printf("NO\n");
            return 0;
        }
        n /= 10;
    }
    printf("YES\n");

    return 0;
}

