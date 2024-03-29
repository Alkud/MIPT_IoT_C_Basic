#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // Таблица истинности для импликации A -> B
    printf("Эквивалент импликации\n");
    printf(" A | B | !A  | !A+B | A->B \n");
    printf("---+---+-----+------+------\n");
    printf(" 0 | 0 |  1  |  1   |  1   \n");
    printf("---+---+-----+------+------\n");
    printf(" 0 | 1 |  1  |  1   |  1   \n");
    printf("---+---+-----+------+------\n");
    printf(" 1 | 0 |  0  |  0   |  0   \n");
    printf("---+---+-----+------+------\n");
    printf(" 1 | 1 |  0  |  1   |  1   \n\n");
    // Таблица истинности для эквиваленции A <-> B
    printf("Эквивалент эквиваленции\n");
    printf(" A | B | A&&B | !A | !B | !A&&!B | (A&&B)+(!A&&!B) | A<->B \n");
    printf("---+---+------+----+----+--------+-----------------+-------\n");
    printf(" 0 | 0 |  0   | 1  | 1  |   1    |        1        |   1   \n");
    printf("---+---+------+----+----+--------+-----------------|-------\n");
    printf(" 0 | 1 |  0   | 1  | 0  |   0    |        0        |   0   \n");
    printf("---+---+------+----+----+--------+-----------------|-------\n");
    printf(" 1 | 0 |  0   | 0  | 1  |   0    |        0        |   0   \n");
    printf("---+---+------+----+----+--------+-----------------+-------\n");
    printf(" 1 | 1 |  1   |  1 | 0  |   0    |        1        |   1   \n");
    return 0;
}

