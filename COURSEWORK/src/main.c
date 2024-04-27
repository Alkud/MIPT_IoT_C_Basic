#include <stdio.h>
#include <unistd.h>

#include "program_arguments.h"
#include "temp_api.h"
#include "csv_reader.h"

// Максимальное число записей, помещающееся на стеке с учётом расходов на сортировку
const uint32_t MAX_DATA_SIZE = 60000;

int main(int argc, char* argv[])
{
    ProgramArguments arguments = {
            .sort_by_temperature = 0,
            .sort_by_date = 0,
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
    if (data_capacity > MAX_DATA_SIZE) {
        data_capacity = MAX_DATA_SIZE;
    }
    TemperatureDataItem data_items[data_capacity];
    TemperatureData temperature_data = CreateTemperatureData(data_capacity, &data_items[0]);

    int res;
    while ((res = GetNextRow(&csv_descriptor)) != EOF) {
        if (BAD_ROW == res) {
            printf("\tигнорирована некорректная строка: %s\n", csv_descriptor.buffer);
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
    }
    CloseFile(&csv_descriptor);

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
    if (arguments.sort_by_date || arguments.sort_by_temperature) {
        uint32_t* items_to_print = NULL;
        if (arguments.items_to_print != 0) {
            items_to_print = &arguments.items_to_print;
        }
        if (arguments.sort_by_date) {
            printf("Сортировка по дате:\n");
            printf("----------+-----+---\n");
            DataRadixSort(&temperature_data, 1);
            PrintData(&temperature_data, 1, items_to_print, &start_date, &start_date_precision);
        }
        if (arguments.sort_by_temperature) {
            printf("Сортировка по температуре:\n");
            printf("----------+-----+---\n");
            DataRadixSort(&temperature_data, 0);
            PrintData(&temperature_data, 1, items_to_print, &start_date, &start_date_precision);
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

    return 0;
}