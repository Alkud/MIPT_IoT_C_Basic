// G9 ДЗ 4
// Удалить повторяющиеся символы
// В файле .txt строка из меленьких и больших английских букв, знаков препинания и пробелов. Требуется удалить из нее повторяющиеся символы и все пробелы. Результат записать в файл .txt. 

// Данные на входе: Строка из меленьких и больших английских букв, знаков препинания и пробелов. Размер строки не более 1000 сивмолов. 
// Данные на выходе: Строка из меленьких и больших английских букв.

#include <stdio.h>
#include <string.h>

const char INPUT_NAME[]  = "input.txt";
const char OUTPUT_NAME[] = "output.txt";
const int STRING_SIZE = 1000;

int open_file(FILE** f, const char* name, const char* modes);
int read_string(FILE* f, char s[], int max_size);
int is_letter(const char c);
int remove_duplicates(char* str, int size);

int main(void)
{
    // читаем строку входного файла
    FILE* input_file = NULL;
    if (!open_file(&input_file, INPUT_NAME, "r")) {
        return -1;
    }
    char input_string[STRING_SIZE];
    int actual_string_size = read_string(input_file, input_string, STRING_SIZE);
    // удаляем повторяющиеся буквы, знаки препинания и пробелы
    int filterd_size = remove_duplicates(input_string, actual_string_size); 
    // выводим уникальные символы в файл
    FILE* output_file = NULL;
    if (!open_file(&output_file, OUTPUT_NAME, "w")) {
        return - 1;
    }
    fprintf(output_file, "%s", input_string);
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

int is_letter(const char c)
{
    if (c >= 'a' && c <= 'z') {
        return 1;
    } else if (c >= 'A' && c <= 'Z') {
        return 2;
    } else {
        return 0;
    }
}

int remove_duplicates(char* str, int size)
{
    int num_entries[52];
    for (int i = 0; i < 52; ++i) {
        num_entries[i] = 0;
    }
    int check_result, char_idx;
    int write_idx = 0;
    for(int read_idx = 0; read_idx <= size; ++read_idx) {
        check_result = is_letter(str[read_idx]);
        if (!check_result) {
            continue;
        }
        if (check_result == 1) {
            // строчные буквы
            char_idx = str[read_idx] - 'a';
        } else {
            // заглавные буквы
            char_idx = 26 + str[read_idx] - 'A';
        }
        if (num_entries[char_idx] == 0) {
            num_entries[char_idx] += 1;
            if (read_idx != write_idx) {
                str[write_idx] = str[read_idx];
            }
            write_idx += 1;
        }
    }
    str[write_idx] = '\0';
    return write_idx;
}