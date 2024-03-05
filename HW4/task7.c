#include <stdio.h>
#include <inttypes.h>


int main() {
    int32_t a = 0;
    int32_t b = 0;
    int32_t c = 0;
    int32_t d = 0;
    int32_t e = 0;
    int32_t max = INT32_MIN;
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
    if (a > max) {
        max = a;
    }
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    if (d > max) {
        max = d;
    }
    if (e > max) {
        max = e;
    }
    printf("%d\n", max);

    return 0;
}

