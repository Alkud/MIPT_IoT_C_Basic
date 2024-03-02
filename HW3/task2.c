#include <stdio.h>
#include <locale.h>
#include <stdint.h>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int32_t A = 0;
    int32_t B = 0;
    int32_t C = 0;
    // сумма и произведение 32-битных знаковых целых могут выйти за диапазон 32-битного знакового целого
    int64_t res = 0;
    printf("Ведите 3 целых числа: \n");
    scanf("%d%d%d", &A, &B, &C);
    res = (int64_t)A + (int64_t)B + (int64_t)C;
    printf("%d+%d+%d=%ld\n", A, B, C, res);
    res = (int64_t)A * (int64_t)B * (int64_t)C;
    printf("%d*%d*%d=%ld\n", A, B, C, res);

    return 0;
}

