#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H

#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char file_name[FILENAME_MAX];
    uint8_t sort_by_date;
    uint8_t sort_by_temperature;
    uint32_t items_to_print;
    uint16_t y;
    uint8_t m;
    uint8_t d;
    uint16_t Y;
    uint8_t M;
    uint8_t D;
} ProgramArguments;

void PrintHelp()
{
    printf("Чтение данных температурного датчика. Вывод статистики за период\n");
    printf("Аргументы командной строки:\n");
    printf("\t-h       вывод справки\n");
    printf("\t-f       имя файла с данными\n");
    printf("\t-s {N}   сортировка по дате и вывод первых N записей интервала\n");
    printf("\t-t {N}   сортировка по температуре и вывод первых N записей интервала\n");
    printf("интервал статистики задаётся:\n\tлибо годом, месяцем и днём\n");
    printf("\t-y YYYY  год (обязательно)\n");
    printf("\t-m MM    месяц (опционально)\n");
    printf("\t-d DD    день (опционально)\n");
    printf("\tлибо границами интервала [y, m, d](начало), [Y, M, D](конец)\n");
    printf("\t-y YYYY год (обязательно)\n");
    printf("\t-m MM   месяц (опционально)\n");
    printf("\t-d DD   день (опционально)\n");
    printf("\t-Y YYYY год (обязательно)\n");
    printf("\t-M MM   месяц (опционально)\n");
    printf("\t-D DD   день (опционально)\n");
}

int ParseArguments(int argc, char* argv[], ProgramArguments* arguments)
{
    int need_help = 0;
    int opt;
    while ( (opt = getopt(argc,argv,":hf:s::t::y:m:d:Y:M:D:")) != -1){
        switch (opt){
            case 'h':
                need_help = 1;
                break;
            case 'f':
                strcpy(arguments->file_name, optarg);
                break;
            case 's':
                arguments->sort_by_date = 1;
                if (optarg != NULL) {
                    sscanf(optarg, "%u", &arguments->items_to_print);
                }
                break;
            case 't':
                arguments->sort_by_temperature = 1;
                break;
            case 'y':
                sscanf(optarg, "%hu", &arguments->y);
                break;
            case 'm':
                sscanf(optarg, "%hhu", &arguments->m);
                break;
            case 'd':
                sscanf(optarg, "%hhu", &arguments->d);
                break;
            case 'Y':
                sscanf(optarg, "%hu", &arguments->Y);
                break;
            case 'M':
                sscanf(optarg, "%hhu", &arguments->M);
                break;
            case 'D':
                sscanf(optarg, "%hhu", &arguments->D);
                break;
            case ':':
                printf("опция -%c требует значения\n", optopt);
                need_help = 1;
            default:
                break;
        };
    };
    if (0 == arguments->file_name[0]) {
        printf("Ошибка! Необходимо указать имя файла -f <data.csv>\n\n");
        need_help = 1;        
    }
    if (0 == arguments->y) {
        printf("Ошибка! Опция -y должна быть указана и иметь значение\n\n");
        need_help = 1;
    }
    if (arguments->y == 0 && (arguments->m != 0 || arguments->d != 0)) {
        printf("Ошибка! Если указана опция -m, должна быть указана опция -y\n");
        printf("        Если указана опция -d, должный быть указаны -y и -m\n");
        need_help = 1;        
    }
    if (arguments->Y == 0 && (arguments->Y != 0 || arguments->D != 0)) {
        printf("Ошибка! Если указана опция -M, должна быть указана опция -Y\n");
        printf("        Если указана опция -D, должный быть указаны -Y и -M\n");
        need_help = 1;        
    }
    if (arguments ->Y != 0 && ((arguments->m != 0 && arguments->M == 0) || (arguments->d != 0 && arguments->D == 0))) {
        printf("Ошибка! Даты y.m.d и Y.M.D  должны быть указаны с одинаковой точностью\n\n");
        need_help = 1;
    }
    return need_help;
}

#endif
