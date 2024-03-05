#include <stdio.h>
#include <inttypes.h>


int main()
{
    int32_t a = 0;
    int32_t b = 0;
    scanf("%d%d", &a, &b);
    if (a < b) {
        printf("%d %d\n", a, b);
    } else {
        printf("%d %d\n", b, a);
    }

    return 0;
}
