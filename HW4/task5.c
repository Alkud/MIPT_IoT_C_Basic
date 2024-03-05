#include <stdio.h>
#include <inttypes.h>


int main()
{
    int32_t x1 = 0;
    int32_t x2 = 0;
    int32_t y1 = 0;
    int32_t y2 = 0;
    float k = 0.0;
    float b = 0.0;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if (x1 != x2) {
        k = ((float)y2 - (float)y1) / ((float)x2 - (float)x1);
        b = (float)y1 - k * (float)x1;
    } else {
        // в условии не уточнено, возможные решения:
        if (y1 != y2) {
            // это - уравнение вида x = k*y + b, т.е. x и y меняются местами
            k = 0.0; // (x1 - x2) / (y1 - y2)
            b = x1 - k * y1;
        } else {
            // это - точка, а не прямая! уравнение точки y = b
            k = 0.0;
            b = y1;
        }
    }
    printf("%.2f %.2f\n", k, b);

    return 0;
}

