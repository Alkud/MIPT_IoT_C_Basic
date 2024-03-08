//B19
//Сумма цифр равна 10
//Ввести натуральное число и определить, верно ли, что сумма его цифр равна 10.

#include <stdio.h>
#include <inttypes.h>


int main() {
    uint32_t n;
    scanf("%u", &n);
    uint8_t sum = 0;
    while (n > 0 && sum <= 10) {
        sum += n % 10;
        n /= 10;
    }
    printf((sum == 10 && n == 0) ? "YES\n" : "NO\n");

    return 0;
}


