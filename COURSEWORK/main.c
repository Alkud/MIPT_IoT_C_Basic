#include <stdio.h>
#include <unistd.h>
#include <locale.h>

#include "program_arguments.h"
#include "temp_api.h"
#include "csv_reader.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    ProgramArguments arguments = {
            .sort_by_temperature = 0,
            .items_to_print = 0,
            .y = 0,
            .m = 0,
            .d = 0,
            .Y = 0,
            .M = 0,
            .D = 0
    };

    int need_help = ParseArguments(argc, argv, &arguments);

    if (need_help) {
        PrintHelp();
        return 0;
    }

    CsvFileDescriptor csv_descriptor;
    strcpy(csv_descriptor.file_name, arguments.file_name);

    if (OpenFile(&csv_descriptor) != 0) {
        printf("Ошибка открытия файла %s\n", csv_descriptor.file_name);
        return -1;
    }

    uint32_t data_capacity = 2 * csv_descriptor.approx_data_size;
    TemperatureData temperature_data = CreateTemperatureData(data_capacity);
    if (NULL == temperature_data.items) {
        printf("Не удалось выделить память для данных\n");
        return -1;
    }

    int res;
    uint32_t lines_count = 0;
    while ((res = GetNextRow(&csv_descriptor)) != EOF) {
        if (BAD_ROW == res) {
            printf("\tигнорирована некорректная строка №%u : %s\n", lines_count, csv_descriptor.buffer);
            continue;
        } 
        TemperatureInfo new_info = {
            .date.yyyy = csv_descriptor.i_yyyy,
            .date.mo = csv_descriptor.i_mo,
            .date.dd = csv_descriptor.i_dd,
            .date.hh = csv_descriptor.i_hh,
            .date.mi = csv_descriptor.i_mi,
            .temperature = csv_descriptor.i_ttt
        };
        if (NULL == AddTemperatureInfo(&temperature_data, &new_info)) {
            printf("Достигнут предельный объём данных!\n");
            break;
        }
        ++lines_count;
    }
    CloseFile(&csv_descriptor);

    DataRadixSort(&temperature_data, 1);
    if (0 == arguments.y) {
        StatisticsArrayRecord per_month_statisitcs[1200];
        uint16_t month_count = PerMonthStatistics(&temperature_data, per_month_statisitcs);
        printf("Статистика месячных температур:\n");
        PrintStatisticsArray(month_count, per_month_statisitcs);
        StatisticsArrayRecord per_year_statisitcs[100];
        uint16_t years_count = PerYearStatistics(&temperature_data, per_year_statisitcs);
        printf("\nСтатистика годовых температур:\n");
        PrintStatisticsArray(years_count, per_year_statisitcs);

        if (arguments.sort_by_temperature) {
            goto temp_sort;
        }

        return 0;     
    }

    Date start_date = {
            .yyyy = arguments.y,
            .mo = arguments.m,
            .dd = arguments.d,
            .hh = 0,
            .mi = 0
    };
    uint32_t start_date_precision = DATE_YEAR_PRECISION;
    if (arguments.m > 0) {
        if (arguments.d > 0) {
            start_date_precision = DATE_DAY_PRECISION;
        } else {
            start_date_precision = DATE_MONTH_PRECISION;
        }
    }

    int8_t temp_min;
    int8_t temp_max;
    float temp_avg;

    if (0 == arguments.Y) {
        // выводим статистику за конкретный месяц года
        ExactDateStatics(&temperature_data, start_date, start_date_precision,
                         &temp_avg, &temp_min, &temp_max);
        printf("Статистика температуры за %hu", start_date.yyyy);
        if (start_date.mo > 0) {
            if (start_date.dd > 0) {
                printf(".%02hhu.%02hhu:\n", start_date.mo, start_date.dd);
            } else {
                printf(".%02hhu:\n", start_date.mo);
            }
        } else {
            printf("-ый год:\n");
        }
        printf("мин.    : %+6.2f градусов\n", (float)temp_min);
        printf("макс.   : %+6.2f градусов\n", (float)temp_max);
        printf("средняя : %+6.2f градусов\n", temp_avg);
    } else {
        // статистика за произвольный интервал
        Date stop_date = {
                .yyyy = arguments.Y,
                .mo = arguments.M,
                .dd = arguments.D,
                .hh = 0,
                .mi = 0
        };
        DateIntervalStatics(&temperature_data, start_date, stop_date, start_date_precision,
                            &temp_avg, &temp_min, &temp_max);
        printf("Статитсика температуры за период %hu", start_date.yyyy);
        if (start_date.mo > 0) {
            if (start_date.dd > 0) {
                printf(".%02hhu.%02hhu - ", start_date.mo, start_date.dd);
            } else {
                printf(".%02hhu - ", start_date.mo);
            }
        } else {
            printf("-ый - ");
        }
        printf ("%hu", stop_date.yyyy);
        if (stop_date.mo > 0) {
            if (stop_date.dd > 0) {
                printf(".%02hhu.%02hhu:\n", stop_date.mo, stop_date.dd);
            } else {
                printf(".%02hhu:\n", stop_date.mo);
            }
        } else {
            printf("-ый годы:\n");
        }
        printf("мин.    : %+6.2f градусов\n", (float)temp_min);
        printf("макс.   : %+6.2f градусов\n", (float)temp_max);
        printf("средняя : %+6.2f градусов\n", temp_avg);
    }

temp_sort:
    if (arguments.sort_by_temperature) {        
        uint32_t* items_to_print = NULL;
        if (arguments.items_to_print != 0) {
            items_to_print = &arguments.items_to_print;
        }
        if (arguments.sort_by_temperature) {
            DataRadixSort(&temperature_data, 0);
            printf("\nСортировка по температуре:\n");
            printf("самые холодные дни:\n");
            printf("------------+-------+-----\n");            
            PrintDataHead(&temperature_data, items_to_print, 1);
            printf("самые тёплые дни:\n");
            printf("------------+-------+-----\n");            
            PrintDataTail(&temperature_data, items_to_print, 1);
        }
    }

    // освобождаем память
    ClearTemperatureData(&temperature_data);
    return 0;
}