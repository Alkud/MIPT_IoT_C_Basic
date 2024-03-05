#include <stdio.h>
#include <inttypes.h>


int main()
{
    int32_t a = 0;
    int32_t b = 0;
    int32_t c = 0;
    int32_t max = 0;
    scanf("%d %d %d", &a, &b, &c);
    if (a > b) {
        max = a > c ? a : c;
    } else {
        max = b > c ? b : c;
    }
    printf("%d\n", max);

    return 0;
}

