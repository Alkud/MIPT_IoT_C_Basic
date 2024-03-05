#include <stdio.h>
#include <inttypes.h>


int main() {
    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;
    uint32_t max = 0;
    uint64_t sum = 0;
    scanf("%d%d%d", &a, &b, &c);
    max = a > b ? a : b;
    max = c > max ? c : max;
    sum = (uint64_t)a + (uint64_t)b + (uint64_t)c;
    // max - наибольшая сторона, (sum - max) сумма двух наименьших сторон
    if ( (sum - (uint64_t)max) <= (uint64_t)max ) {
        printf("NO\n");
    } else {
        printf("YES\n");
    }
    return 0;
}
