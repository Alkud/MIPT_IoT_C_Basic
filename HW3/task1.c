#include <stdio.h>
#include <locale.h>
#include <stdint.h>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int32_t A = 0;
    int32_t B = 0;
    int32_t C = 0;
    // сумма 32-битных знаковых целых может выйти за диапазон 32-битного знакового целого
    int64_t sum = 0;
    printf("Ведите 3 целых числа: \n");
    scanf("%d%d%d", &A, &B, &C);
    sum = (int64_t)A + (int64_t)B + (int64_t)C;
    printf("%d+%d+%d=%ld\n", A, B, C, sum);

    return 0;
}

