#include <stdio.h>
#include <locale.h>
#include <stdint.h>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int32_t A = 0;
    int32_t B = 0;
    // разность 32-битных знаковых целых может выйти за диапазон 32-битного знакового целого
    int64_t diff = 0;
    printf("Ведите 2 целых числа: \n");
    scanf("%d%d", &A, &B);
    diff = (int64_t)A - (int64_t)B;
    printf("%ld\n", diff);

    return 0;
}

