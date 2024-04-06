// G4 ДЗ 1
// По одному разу
// В файле .txt даны два слова не более 100 символов каждое, разделенные одним пробелом. Найдите только те символы слов, которые встречаются в обоих словах только один раз. Напечатайте их через пробел в файл .txt в лексикографическом порядке. 

// Данные на входе: Два слова из маленьких английских букв через пробел. Длина каждого слова не больше 100 символов. 
// Данные на выходе: Маленькие английские буквы через пробел.

#include <stdio.h>
#include <string.h>

#define WORD_SIZE 100
#define STR_(x) #x
#define STR(x) STR_(x)
const char INPUT_NAME[]  = "input.txt";
const char OUTPUT_NAME[] = "output.txt";

int open_file(FILE** f, const char* name, const char* modes);
void read_two_words(FILE* f, char* w1, char* w2);
void single_entry_characters(const char* w1, const char* w2, int* indices, int* size);


int main(void)
{
    // читаем слова из входного файла
    FILE* input_file = NULL;
    if (!open_file(&input_file, INPUT_NAME, "r")) {
        return -1;
    }
    char word_1[WORD_SIZE];
    char word_2[WORD_SIZE];
    read_two_words(input_file, &word_1[0], &word_2[0]);
    fclose(input_file);
    // ищем нужные символы
    int single_entry_codes[26];
    int num_single_entry_chars = 0;
    single_entry_characters(word_1, word_2, single_entry_codes, &num_single_entry_chars);
    // выводим символы в файл
    FILE* output_file = NULL;
    if (!open_file(&output_file, OUTPUT_NAME, "w")) {
        return - 1;
    }
    for (int i = 0; i < num_single_entry_chars; ++i) {
        if (i > 0) {
            fprintf(output_file, " ");
        }
        putc('a' + single_entry_codes[i], output_file);
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

void read_two_words(FILE* f, char* w1, char* w2)
{
    fscanf(f, "%" STR(WORD_SIZE) "s", w1);
    fscanf(f, "%" STR(WORD_SIZE) "s", w2);
}

void single_entry_characters(const char* w1, const char* w2, int* indices, int* size)
{
    int num_entries[26];
    for (int i = 0; i < 26; ++i) {
        num_entries[i] = 0;
    }
    for(int i = 0; w1[i] != '\0'; ++i) {
        int char_idx = w1[i] - 'a';
        if (num_entries[char_idx] == -1) {
            continue;
        }        
        num_entries[char_idx] += 1;
        if (2 == num_entries[char_idx]) {
            num_entries[char_idx] = -1;
        }
    }
    for(int i = 0; w2[i] != '\0'; ++i) {
        int char_idx = w2[i] - 'a';
        if (num_entries[char_idx] == -1) {
            continue;
        }
        num_entries[char_idx] += 10;
        if (num_entries[char_idx] > 11) {
            num_entries[char_idx] = -1;
        }        
    }
    *size = 0;
    for (int i = 0; i < 26; ++i) {
        if (num_entries[i] == 11) {
            indices[*size] = i;
            *size += 1;
        }
    }
}