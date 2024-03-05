#include <stdio.h>
#include <inttypes.h>


int main()
{
    int32_t a = 0;
    int32_t max = INT32_MIN;
    int32_t min = INT32_MAX;
    scanf("%" SCNd32, &a);
    if (a > max) {
        max = a;
    }
    if (a < min) {
        min = a;
    }
    scanf("%" SCNd32, &a);
    if (a > max) {
        max = a;
    }
    if (a < min) {
        min = a;
    }
    scanf("%" SCNd32, &a);
    if (a > max) {
        max = a;
    }
    if (a < min) {
        min = a;
    }
    scanf("%" SCNd32, &a);
    if (a > max) {
        max = a;
    }
    if (a < min) {
        min = a;
    }
    scanf("%" SCNd32, &a);
    if (a > max) {
        max = a;
    }
    if (a < min) {
        min = a;
    }
    printf("%" PRId64 "\n", (int64_t)max + (int64_t)min);

    return 0;
}

