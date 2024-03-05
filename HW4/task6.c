#include <stdio.h>
#include <inttypes.h>


int main()
{
    int32_t a = 0;
    int32_t b = 0;
    scanf("%d%d", &a, &b);
    if (a > b) {
        printf("Above\n");
    } else if (a < b){
        printf("Less\n");
    } else {
        printf("Equal\n");
    }

    return 0;
}

