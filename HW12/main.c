#include <stdio.h>

#include "temp_api.h"

#include "radix_sort.h"

const uint32_t MAX_DATA_SIZE = 2 * 365U;

int main(int argc, char* argv[])
{
    TemperatureDataItem data_items[MAX_DATA_SIZE];
    TemperatureData temperature_data = CreateTemperatureData(MAX_DATA_SIZE, &data_items[0]);

    Date test_date_1 = {
        .yyyy = 2024,
        .mo = 4,
        .dd = 12,
        .hh = 11,
        .mi = 37
    };
    Date test_date_2 = {
        .yyyy = 2024,
        .mo = 4,
        .dd = 12,
        .hh = 11,
        .mi = 38
    };    
    printf("%u - %u = %ld\n", DateToInt(&test_date_1, DATE_MINUTE_PRECISION),
           DateToInt(&test_date_2, DATE_MINUTE_PRECISION), DateDiff(&test_date_1, &test_date_2, DATE_MINUTE_PRECISION));
    printf("%u - %u = %ld\n", DateToInt(&test_date_1, DATE_MONTH_PRECISION),
           DateToInt(&test_date_2, DATE_MONTH_PRECISION), DateDiff(&test_date_1, &test_date_2, DATE_MONTH_PRECISION));           
    printf("%u\n", (2024U << 20) + (4U << 16) + (12 << 11) + (11 << 6) + 37);
    DateString date_str;
    DateToStr(&test_date_1, &date_str);
    printf("%s\n", date_str.str);

    TemperatureInfo new_info = {
        .date = {
            .yyyy = 2024,
            .mo = 6,
            .dd = 25,
            .hh = 19,
            .mi = 49
        },
        .temperature = 17
    };
    AddTemperatureInfo(&temperature_data, &new_info);
    InfoString info_str;
    InfoToStr(&temperature_data.root->info, &info_str, 1);
    printf("%s\n", info_str.str);

    // new_info.date.mo = 11;
    // new_info.date.dd = 1;
    // new_info.date.hh = 4;
    new_info.date.mi = 48;
    //new_info.temperature = 18;

    AddTemperatureInfo(&temperature_data, &new_info);
    InfoToStr(&temperature_data.last->info, &info_str, 0);
    printf("%s\n", info_str.str);

    // RemoveTemperatureInfoByValue(&temperature_data, &new_info);
    // InfoToStr(&temperature_data.last->info, &info_str, 0);
    // printf("%s\n", info_str.str);    
    
    // RemoveTemperatureInfoByPtr(&temperature_data, temperature_data.last);
    // InfoToStr(&temperature_data.last->info, &info_str, 0);
    // printf("%s\n", info_str.str);        

    // RemoveTemperatureInfoByPtr(&temperature_data, temperature_data.last);
    // InfoToStr(&temperature_data.last->info, &info_str, 1);
    // printf("%s\n", info_str.str);        

    printf ("%lu, %lu, %lu\n", sizeof(PackedDate), sizeof(PackedInfoDatePriority), sizeof(PackedInfoTemperaturePriority));

    SortTemperatureInfoByDate(&temperature_data);
    ITEM_PTR data_ptr = temperature_data.root;
    // while(data_ptr != NULL) {
    //     InfoToStr(&data_ptr->info, &info_str, 0);
    //     printf("%s\n", info_str.str);   
    // }


    uint64_t test_array[] = {1, 2345, 982394823, 3425345, 345, 934};
    RadixSort(6, test_array);
    return 0;
}