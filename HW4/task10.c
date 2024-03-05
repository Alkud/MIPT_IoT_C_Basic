#include <stdio.h>
#include <inttypes.h>


int main() {
    uint8_t month = 0;
    scanf("%" SCNu8, &month);
    if (month < 3 || month > 11) {
        printf("winter\n");
    } else if (month < 6) {
        printf("spring\n");
    } else if (month < 9) {
        printf("summer\n");
    } else {
        printf("autumn\n");
    }

    return 0;
}
