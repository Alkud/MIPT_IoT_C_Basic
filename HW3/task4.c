#include <stdio.h>
#include <locale.h>
#include <stdint.h>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int32_t A = 0;
    int32_t B = 0;
    int32_t C = 0;
    float sum = 0.0;
    printf("Ведите 3 целых числа: \n");
    scanf("%d%d%d", &A, &B, &C);
    sum = (float)A + (float)B + (float)C;
    printf("%.2f\n", sum / 3.0);

    return 0;
}

