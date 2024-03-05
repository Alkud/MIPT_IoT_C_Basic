#include <stdio.h>
#include <inttypes.h>


int main() {
    int32_t a = 0;
    int32_t b = 0;
    scanf("%d", &a);
    b = a;
    scanf("%d", &a);
    if (a < b) {
        printf("NO\n");
        return 0;
    }
    b = a;
    scanf("%d", &a);
    if (a < b) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    return 0;
}
