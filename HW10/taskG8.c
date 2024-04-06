// G8 ДЗ 3
// Числа в массив
// В файле .txt дана строка, не более 1000 символов, содержащая буквы, целые числа и иные символы.
// Требуется все числа, которые встречаются в строке, поместить в отдельный целочисленный массив.
// Например, если дана строка "data 48 call 9 read13 blank0a", то в массиве числа 48, 9, 13 и 0. Вывести массив по возрастанию в файл .txt. 
// Данные на входе: Строка из английских букв, цифр и знаков препинания 
// Данные на выходе: Последовательность целых чисел отсортированная по возрастанию

#include <stdio.h>
#include <string.h>

const char INPUT_NAME[]  = "input.txt";
const char OUTPUT_NAME[] = "output.txt";
const int MAX_ITEMS_NUMBER = 500;

int open_file(FILE** f, const char* name, const char* modes);
int read_numbers(FILE* f, int* numbers);
int string_to_integer(const char* str);
void swap(int* a, int* b);
void bubble_sort(int array[], int size);

int main(void)
{
    // читаем числа из входного файла
    FILE* input_file = NULL;
    if (!open_file(&input_file, INPUT_NAME, "r")) {
        return -1;
    }
    int numbers[MAX_ITEMS_NUMBER];
    int no_of_items = read_numbers(input_file, &numbers[0]);
    // сортируем
    bubble_sort(numbers, no_of_items);
    // выводим числа в файл
    FILE* output_file = NULL;
    if (!open_file(&output_file, OUTPUT_NAME, "w")) {
        return - 1;
    }
    for (int i = 0; i < no_of_items; ++i) {
        if (i > 0) {
            fprintf(output_file, " ");
        }
        fprintf(output_file, "%d", numbers[i]);
    }
    putc('\n', output_file);
    fclose(output_file);
    return 0;
}


int open_file(FILE** f, const char* name, const char* modes)
{
    *f = fopen(name, modes);
    if (NULL == *f) {
        printf("Failed to open %s\n", name);
        perror(NULL);
        return 0;
    }
    return 1;
}

int string_to_integer(const char* str)
{
    int n = 0;
    for(const char* c = str; *c != '\0'; ++c) {
        n = (*c - '0') + n*10;
    }
    return n;
}

int read_numbers(FILE* f, int* numbers)
{
    int size = 0;
    char tmp[MAX_ITEMS_NUMBER * 2];
    do{
        if (fscanf(f, "%[0-9]", tmp) == 1) {
            numbers[size] = string_to_integer(tmp);
            size += 1;
        }
    } while (getc(f) != EOF);
    return size;
}

void swap(int* a, int* b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

void bubble_sort(int array[], int size)
{
    int no_swap;
    for(int i = 0; i < size; ++i) {
        no_swap = 1;
        for(int j = size - 1; j > i; --j) {
            if(array[j-1] > array[j])
            {
                swap(&array[j], &array[j-1]);
                no_swap = 0;
            }
        }
        if (no_swap) {
            break;
        }
    }
}