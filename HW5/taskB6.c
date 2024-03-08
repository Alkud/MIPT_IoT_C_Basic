//B6 Урок 5 Практика №2
//Две одинаковые цифры рядом
//Ввести целое число и определить, верно ли, что в его записи есть две одинаковые цифры, стоящие рядом.
//Данные на входе: Одно целое число
//Данные на выходе:	Единственное слов: YES или NO

#include <stdio.h>
#include <inttypes.h>


int main()
{
    int32_t n;
    scanf("%d", &n);
    if (n > -10 && n < 10) {
        // введено однозначное число
        printf("NO\n");
        return 0;
    }
    int8_t prevDigit = n % 10;
    int8_t currDigit;
    do {
        n /= 10;
        currDigit = n % 10;
        if ((n > -10 && n < 10) || currDigit == prevDigit) {
            break;
        }
        prevDigit = currDigit;
    } while (1);
    printf(currDigit == prevDigit ? "YES\n" : "NO\n");

    return 0;
}
