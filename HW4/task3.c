#include <stdio.h>
#include <inttypes.h>


int main()
{
    // на входе гарнатируется целое число в дипазоне 000...999
    uint16_t a;
    uint8_t d0 = 0;
    uint8_t d1 = 0;
    uint8_t d2 = 0;
    uint8_t max = 0;
    scanf("%" SCNu16, &a);
    d0 = a % 10;
    d1 = (a / 10) % 10;
    d2 = (a / 100) % 10;
    if (d0 > d1) {
        max = d0 > d2 ? d0 : d2;
    } else {
        max = d1 > d2 ? d1 : d2;
    }
    printf("%" PRIu8 "\n", max);

    return 0;
}


