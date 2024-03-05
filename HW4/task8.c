#include <stdio.h>
#include <inttypes.h>


int main() {
    int32_t a = 0;
    int32_t b = 0;
    int32_t c = 0;
    int32_t d = 0;
    int32_t e = 0;
    int32_t min = INT32_MAX;
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
    min = a < b ? a : b;
    min = c < min ? c : min;
    min = d < min ? d : min;
    min = e < min ? e : min;
    printf("%d\n", min);

    return 0;
}

