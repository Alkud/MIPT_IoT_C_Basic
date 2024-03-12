// C13 Практика
// Вычислить cos
// Составить функцию, которая вычисляет синус как сумму ряда (с точностью 0.001)
//
// cos(x) = 1 - x2/2! + x4/4! - x6/6! + ...
// (x в радианах)
// float cosinus(float x)
//
// Данные на входе: Целое число от 0 до 90
// Данные на выходе: Вещественное число в формате "%.3f"


#include <stdio.h>
#include <math.h>

const float PI = 3.1415926535;

float cosinus(float x);

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("%.3f\n", cosinus(n * PI / 180.0));
}


float cosinus(float x)
{
    float cos = 0.0;
    float x_n = 1.0;
    int n = 1;
    do {
        cos += x_n;
        x_n *= -1.0 * x * x / ((2 * n) * (2 * n - 1));
        n += 1;
    } while(fabs(x_n) > 0.001);

    return cos;
}

