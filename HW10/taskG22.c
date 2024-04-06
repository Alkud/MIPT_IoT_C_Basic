// G22
// Soundex
// Известный алгоритм Soundex (https://ru.wikipedia.org/wiki/Soundex) определяет, похожи ли два английских слова по звучанию.
// На вход он принимает слово и заменяет его на некоторый четырёхсимвольный код. Если коды двух слов совпадают, то слова, как правило, звучат похоже.
// Вам требуется реализовать этот алгоритм. Он работает так:
// Первая буква слова сохраняется.
// В остальной части слова:
// буквы, обозначающие, как правило, гласные звуки: a, e, h, i, o, u, w и y — отбрасываются;
// оставшиеся буквы (согласные) заменяются на цифры от 1 до 6, причём похожим по звучанию буквам соответствуют одинаковые цифры:
// 1: b, f, p, v
// 2: c, g, j, k, q, s, x, z
// 3: d, t
// 4: l
// 5: m, n
// 6: r
// Любая последовательность одинаковых цифр сокращается до одной такой цифры. Итоговая строка обрезается до первых четырёх символов.
// Если длина строки меньше требуемой, недостающие символы заменяются знаком 0.
// Примеры:
// аmmonium → ammnm → a5555 → a5 → a500
// implementation → implmnttn → i51455335 → i514535 → i514
// Данные на входе: Во входном файле .txt находится одно непустое слово, записанное строчными латинскими буквами. Длина слова не превосходит 20 символов. 
// Данные на выходе: Напечатайте четырёхбуквенный код, соответствующий слову в файл .txt. 

#include <stdio.h>
#include <string.h>

const char INPUT_NAME[]  = "input.txt";
const char OUTPUT_NAME[] = "output.txt";
const int WORD_SIZE = 1000;
const char VOWELS[8] = {'a', 'e', 'h', 'i', 'o', 'u', 'w', 'y'};
const char CONSONANTS[6][8] = {
    {'b', 'f', 'p', 'v', '\0'},
    {'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'},
    {'d', 't', '\0'},
    {'l', '\0'},
    {'m', 'n', '\0'},
    {'r', '\0'}
};

int open_file(FILE** f, const char* name, const char* modes);
int is_vowel(char c);
int remove_vowels(char* str);
int cons_code(const char c);
void encode_consonants(char* str, int size);
int is_digit(char c);
int remove_digit_duplicates(char* str, int size, int max_out_size);
void soundex(char* source);


int main(void)
{
    // читаем строку входного файла
    FILE* input_file = NULL;
    if (!open_file(&input_file, INPUT_NAME, "r")) {
        return -1;
    }
    char input_string[WORD_SIZE];
    fscanf(input_file, "%s", input_string);
    // кодируем
    soundex(input_string);
    // выводим код в файл
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

int is_vowel(const char c)
{
    for (int i = 0; i < 8; ++i) {
        if (c == VOWELS[i]) {
            return 1;
        }
    }
    return 0;
}

int remove_vowels(char* str)
{
    int read_idx = 1;
    int write_idx = 1;
    while(str[read_idx] != '\0')
    {
        if (!is_vowel(str[read_idx])) {
            if (write_idx != read_idx) {
                str[write_idx] = str[read_idx];
            }            
            write_idx += 1;
        }
        read_idx += 1;
    };
    str[write_idx] = '\0';
    return write_idx;
}

int cons_code(const char c)
{
    for (int m = 0; m < 6; ++m) {
        for (int n = 0; n < 8 && CONSONANTS[m][n] != '\0'; ++n) {
            if (c == CONSONANTS[m][n]) {
                return m;
            }
        }
    }
    return 0;
}

void encode_consonants(char* str, const int size)
{
    for (int i = 1; i < size; ++i) {
        str[i] = '1' + cons_code(str[i]);
    }
}

int is_digit(const char c) {
    return (c >= '0' && c <= '9');
}

int remove_digit_duplicates(char* str, const int size, const int max_out_size)
{
    int write_idx = 1;
    for(int read_idx = 1; read_idx < size && write_idx < max_out_size; ++read_idx) {
        if (is_digit(str[read_idx]) && str[read_idx] != str[read_idx - 1]) {
            if (write_idx != read_idx) {
                str[write_idx] = str[read_idx];
            }
            write_idx += 1;
        }
    }
    if (write_idx < max_out_size) {
        for (; write_idx < max_out_size; ++write_idx) {
            str[write_idx] = '0';
        }
    }
    str[write_idx] = '\0';
    return write_idx;
}

void soundex(char* str)
{
    int size = remove_vowels(str);
    encode_consonants(str, size);
    remove_digit_duplicates(str, size, 4);
}