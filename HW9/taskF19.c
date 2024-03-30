// F19 ДЗ 6 
// Больше среднего
// Написать функцию и программу, демонстрирующую работу данной функции.
// Определить количество положительных элементов квадратной матрицы, превышающих по величине среднее арифметическое всех элементов главной диагонали.
// Реализовать функцию среднее арифметическое главной диагонали. 

// Данные на входе: 5 строк по 5 целых чисел через пробел 
// Данные на выходе: Одно целое число

#include <stdio.h>

enum {MATRIX_SIZE = 5};

void scan_matrix(int n, int matrix[n][n]);
float mean_matrix_diag(int n, int matrix[n][n]);
int num_positive_items(int n, int matrix[n][n], float threshold);


int main(void)
{
    int input_matrix[MATRIX_SIZE][MATRIX_SIZE];
    scan_matrix(MATRIX_SIZE, input_matrix);
    float thresh = mean_matrix_diag(MATRIX_SIZE, input_matrix);
    printf("%d\n", num_positive_items(MATRIX_SIZE, input_matrix, thresh));

    return 0;
}


void scan_matrix(int n, int matrix[n][n])
{
    for (int i = 0; i < n * n; ++i) {
        int row_index = i / n;
        int col_index = i % n;
        scanf("%d", &matrix[row_index][col_index]);
    }
}

float mean_matrix_diag(int n, int matrix[n][n])
{
    float sum = 0.0F;
    for (int i = 0; i < n; ++i) {
        sum += matrix[i][i];
    }
    return sum / n;
}

int num_positive_items(int n, int matrix[n][n], float threshold)
{
    int count = 0;
    for (int i = 0; i < n * n; ++i) {
        int row_index = i / n;
        int col_index = i % n;
        if ((float)matrix[row_index][col_index] > threshold) {
            count += 1;
        }
    }
    return count;
}


