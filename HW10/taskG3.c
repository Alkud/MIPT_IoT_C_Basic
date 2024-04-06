// G3 Практ 1
// Последний номер символа
// В файле .txt дана строка из 1000 символов. Показать номера символов, совпадающих с последним символом строки. Результат записать в файл .txt 

// Данные на входе: Строка не более 1000 символов 
// Данные на выходе: Целые числа через пробел - номера символа, который совпадает с последним символом строки. 


#include <stdio.h>
#include <string.h>

const char INPUT_NAME[]  = "input.txt";
const char OUTPUT_NAME[] = "output.txt";
const size_t STRING_SIZE = 1000;

int open_file(FILE** f, const char* name, const char* modes);
int read_string(FILE* f, char s[], int max_size);

int main(void)
{    
    // читаем строку из входного файла
    FILE* input_file = NULL;
    if (!open_file(&input_file, INPUT_NAME, "r")) {
        return -1;
    }
    char input_string[STRING_SIZE];
    int actual_string_size = read_string(input_file, input_string, STRING_SIZE);
    fclose(input_file);
    // выводим номера символов в выходной файл
    FILE* output_file = NULL;
    if (!open_file(&output_file, OUTPUT_NAME, "w")) {
        return - 1;
    }
    for (int i = 0; i < actual_string_size; ++i) {
        if (input_string[i] == input_string[actual_string_size]) {
            fprintf(output_file, "%d ", i);
        }
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

int read_string(FILE* f, char s[], int max_size)
{
    char c;
    int idx = 0;
    while (((c = getc(f)) != EOF) && c != '\0' && c != '\n' && idx < max_size-1) {
        s[idx] = c;
        idx += 1;
    }
    s[idx] = '\0';
    return idx - 1;
}