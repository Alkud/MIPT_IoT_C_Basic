#include "temp_api.h"

#include <stdlib.h>
#include <stdio.h>


// Создание массива TemperatureInfo
// Возвращает структуру с массивом элементов и служебными данными
TemperatureData CreateTemperatureData(const uint32_t capacity, const ITEM_PTR zero_item)
{
    TemperatureData data = {
        .items = zero_item,
        .capacity = capacity,
        .root = NULL,
        .last = NULL,
        .cue = NULL,
        .size = 0U
    };
    for(uint32_t i = 0; i < capacity; ++i) {
        data.items[i].info = NULL_INFO;
        data.items[i].next = NULL;
        data.items[i].empty = 1U;
    }
    return data;
}

// Добавление записи в массив
// Возвращает указатель на добавленный элемент
ITEM_PTR AddTemperatureInfo(DATA_PTR const data, INFO_PTR const info)
{
    if (data->size + 1 > data->capacity) {
        // не удалсь вставить новый элемент, индекс последнего элемента не изменился
        return NULL;
    }
    if (0U == data->size) {
        data->items[0].info = *info;
        data->items[0].next = NULL;
        data->root = &(data->items[0]);
        data->last = data->root;
    } else {
        TemperatureDataItem* destination;
        if (data->cue != NULL) {
        // есть освободившиеся елементы
            destination = data->cue;
            data->cue = data->cue->next;
        } else {
            destination = &data->items[data->size];
        }
        // записываем информацию
        destination->empty = 0;
        destination->info = *info;
        destination->next = NULL;
        // обновляем указатели на последний элемент
        data->last->next = destination;
        data->last = destination;
    }
    data->size += 1;
    return data->last;
}

// Сброс элемента массива
ITEM_PTR ResetDataItem(ITEM_PTR const item)
{
    if (NULL == item) {
        return NULL;
    }
    item->empty = 1U;
    item->info = NULL_INFO;
    ITEM_PTR next = item->next;
    item->next = NULL;
    return next;
}

ITEM_PTR PrevDataItem(DATA_PTR const data, ITEM_PTR const item)
{
    if (NULL == data || NULL == item) {
        return NULL;
    }
    uint32_t i = 0;
    for(; i < data->capacity; ++i) {
        if (item == data->items[i].next) {
            return &(data->items[i]);
        }
    }
    return NULL;
}

// Удаление записи из массива по указателю на элемент
// Возвращает указатель на элемент, следующий за удалённым
ITEM_PTR RemoveTemperatureInfoByPtr(DATA_PTR data, ITEM_PTR item)
{
    if (NULL == data || 0 == data->size || item == NULL) {
        return NULL;
    }
    ITEM_PTR prev = NULL;
    ITEM_PTR next = NULL;
    if (item == data->root) {
        //  удаляем корневой элемент - корневым становится следующий
        data->root = ResetDataItem(item);
    } else {
        // сбрасываем, находим предыдущий и следующий за удаляемым элемент
        prev = PrevDataItem(data, item);
        next = ResetDataItem(item);
    }    
    if (prev != NULL) {
        // если у удаляемого есть предыдущий элемент, его следующим становится следующий удаляемого
        prev->next = next;
    }
    if (data->last == item) {
        // если удаляется последний элемент, последним становится предыдущий
        data->last = prev;
    }
    data->size -= 1;
    if (NULL == data->cue) {
        if (data->size > 0) {
            data->cue = item;
        }
    } else {
        data->cue->next = item;
    }
    return next;
}

// Удаление записи из массива по значению элемента
// Возвращает указатель на элемент, следующий за удалённым
ITEM_PTR RemoveTemperatureInfoByValue(DATA_PTR data, INFO_PTR info)
{
    if (NULL == data || 0 == data->size) {
        return NULL;
    }
    // находим первый элемент, равный указанному значению
    ITEM_PTR item = data->root;
    while (item->next != NULL && InfoDiff(&item->info, info, INFO_DP_MINUTE_PRECISION) != 0) {
        item = item->next;
    }
    if (item != NULL) {
        return RemoveTemperatureInfoByPtr(data, item);
    } else {
        return NULL;
    }
}

uint32_t DateToInt(Date* date, uint32_t precision)
{
    DateUnion proxy = {
        .date.yyyy = date->yyyy,
        .date.mo = date->mo,
        .date.dd = date->dd,
        .date.hh = date->hh,
        .date.mi = date->mi
    };
    return proxy.long_word & precision;
}

void IntToDate(uint32_t int_value, Date* date, uint32_t precision)
{
    DateUnion proxy = {
        .long_word = int_value & precision
    };
    date->yyyy = proxy.date.yyyy;
    date->mo = proxy.date.mo;
    date->dd = proxy.date.dd;
    date->hh = proxy.date.hh;
    date->mi = proxy.date.mi;
}

void DateToStr(Date* date, DateString* date_str)
{
    if (NULL == date) {
        sprintf(
            date_str->str, " %04hu.%02hhu.%02hhu | %02hhu:%02hhu ",
            NULL_INFO.date.yyyy, NULL_INFO.date.mo, NULL_INFO.date.dd, NULL_INFO.date.hh, NULL_INFO.date.mi);    
    } else {
        sprintf(date_str->str, " %04hu.%02hhu.%02hhu | %02hhu:%02hhu ", date->yyyy, date->mo, date->dd, date->hh, date->mi);
    }
}

uint64_t InfoToInt(TemperatureInfo* info, uint64_t date_precision)
{
    if (date_precision & 0b1111111100000000000000000000000000000000UL) {
        // приоритет даты
        InfoUnionDatePriority proxy = {
            .info.temperature = info->temperature,
            .info.mi = info->date.mi,
            .info.hh = info->date.hh,
            .info.dd = info->date.dd,
            .info.mo = info->date.mo,
            .info.yyyy = info->date.yyyy
        };
        return proxy.long_long_word;
    } else {
        // приоритет температуры
        InfoUnionTemperaturePriority proxy = {
            .info.mi = info->date.mi,
            .info.hh = info->date.hh,
            .info.dd = info->date.dd,
            .info.mo = info->date.mo,
            .info.yyyy = info->date.yyyy,
            .info.temperature = info->temperature,
        };
        return proxy.long_long_word;
    }
}

void InfoToStr(TemperatureInfo* info, InfoString* info_str, uint8_t border)
{
    if (NULL == info || NULL == info_str) {
        return;
    }
    DateString ds;
    DateToStr(&info->date, &ds);
    const char* row_delimiter = border ? "\n------------+-------+-----" : "";
    if (0 == info->temperature) {
        sprintf(info_str->str, "%s| 0 %s", ds.str, row_delimiter);
    } else {
        sprintf(info_str->str, "%s| %+3d%s", ds.str, info->temperature, row_delimiter);
    }
}

void PrintInfo(TemperatureInfo* info, uint8_t border)
{
    InfoString info_str;
    InfoToStr(info, &info_str, border);
    printf("%s\n", info_str.str);    
}

void PrintData(DATA_PTR data, ITEM_PTR first_item, Date* start_date, uint32_t* date_precision,
               uint32_t* num_items, uint8_t border)
{
    // если не указаны ни кол-во выводимых елементов, ни начальная дата, печатаем весь массив
    ITEM_PTR current;
    if (start_date != NULL && date_precision != NULL) {
        uint32_t current_idx = 0;
        while(current != NULL && DateDiff(&current->info.date, start_date, *date_precision) < 0) {
            current = current->next;
            ++current_idx;
        }
    } else {
        if (NULL == first_item) {
            current = data->root;
        } else {
            current = first_item;
        }
    }
    if (NULL == current) {
        // если не найдена дата или неверно указан элемента, печатаем с начала
        current = data->root;
    }
    uint32_t item_count = 0;
    while(current != NULL && item_count < *num_items) {
        ++item_count;
        PrintInfo(&current->info, border);
        current = current->next;
    }
}

void PrintDataHead(DATA_PTR data, uint32_t* num_items, uint8_t border)
{
    PrintData(data, NULL, NULL, NULL, *num_items > data->size ? &data->size : num_items, border);
}

void PrintDataTail(DATA_PTR data, uint32_t* num_items, uint8_t border)
{  
    ITEM_PTR current = data->root;
    if (*num_items > data->size) {
        PrintData(data, NULL, NULL, NULL, &data->size, border);
    }
    uint32_t item_index = 0;
    while (current != NULL && item_index < (data->size - *num_items)) {
        current = current->next;
        ++item_index;
    }
    PrintData(data, current, NULL, NULL, num_items, border);
}

// Функция сравнения дат с указанием полей для сравнения
// Возвращает - отрицательное целое (меньше), 0 (равно), положительное целое (больше)
int64_t DateDiff(Date* date_a, Date* date_b, uint32_t precision)
{
    return (int64_t)DateToInt(date_a, precision) - (int64_t)DateToInt(date_b, precision);
}

// Функция сравнения TemperatureInfo с указанием порядка полей (приоритет температуры / даты)
int64_t InfoDiff(INFO_PTR info_a, INFO_PTR info_b, uint64_t date_precision)
{
    return (int64_t)InfoToInt(info_a, date_precision) - (int64_t)InfoToInt(info_b, date_precision);
}

// перестановка элементов списка
void SwapDataItems(DATA_PTR data, ITEM_PTR a, ITEM_PTR b)
{
    if (NULL == data || NULL == a || NULL == b) {
        return;
    }
    ITEM_PTR a_prev = PrevDataItem(data, a);
    ITEM_PTR b_prev = PrevDataItem(data, b);
    if (a_prev != NULL) {
        a_prev->next = b;
    }
    if (b_prev != NULL) {
        b_prev->next = a;
    }
    ITEM_PTR tmp = a->next;
    a->next = b->next;
    b->next = tmp;
}

// Возвращает цифру из информационной записи
// yyyy.mo.dd.hh.mi.ttt (приоритет даты) или ttt.yyyy.mo.dd.hh.mi (приоритет температуры)
uint8_t InfoDigit(INFO_PTR info, uint8_t pos, uint8_t date_priority)
{
    uint8_t digit = 0;
    if (date_priority) {
        switch (pos)
        {
        case 0:
            // младшая цифра температуры
            digit = (info->temperature + UINT8_MAX) % 10;
            break;
        case 1:
            digit = ((info->temperature + UINT8_MAX) / 10) % 10;
            break;
        case 2:
            // старшая цифра температуры
            digit = ((info->temperature + UINT8_MAX) / 100) % 10;
            break;
        case 3:
            digit = (info->date.mi) % 10;
            break;
        case 4:
            digit = ((info->date.mi) / 10) % 10;
            break;
        case 5:
            digit = (info->date.hh) % 10;
            break;
        case 6:
            digit = ((info->date.hh) / 10) % 10;
            break;
        case 7:
            digit = (info->date.dd) % 10;
            break;            
        case 8:
            digit = ((info->date.dd) / 10) % 10;
            break;
        case 9:
            digit = (info->date.mo) % 10;
            break;            
        case 10:
            digit = ((info->date.mo) / 10) % 10;
            break;
        case 11:
            // младшая цифра года
            digit = (info->date.yyyy) % 10;
            break;
        case 12:
            digit = ((info->date.yyyy) / 10) % 10;
            break;
        case 13:
            digit = ((info->date.yyyy) / 100) % 10;
            break;
        case 14:
            // старшая цифра года
            digit = ((info->date.yyyy) / 1000) % 10;
            break;            
        default:
            break;
        }
    } else {
        switch (pos)
        {
        case 0:
            // младшая цифра года
            digit = (info->date.yyyy) % 10;
            break;
        case 1:
            digit = ((info->date.yyyy) / 10) % 10;
            break;
        case 2:
            digit = ((info->date.yyyy) / 100) % 10;
            break;
        case 3:
            // старшая цифра года
            digit = ((info->date.yyyy) / 1000) % 10;
            break;    

        case 4:
            digit = (info->date.mi) % 10;
            break;
        case 5:
            digit = ((info->date.mi) / 10) % 10;
            break;
        case 6:
            digit = (info->date.hh) % 10;
            break;
        case 7:
            digit = ((info->date.hh) / 10) % 10;
            break;
        case 8:
            digit = (info->date.dd) % 10;
            break;            
        case 9:
            digit = ((info->date.dd) / 10) % 10;
            break;
        case 10:
            digit = (info->date.mo) % 10;
            break;            
        case 11:
            digit = ((info->date.mo) / 10) % 10;
            break;
        case 12:
            // младшая цифра температуры
            digit = (info->temperature + UINT8_MAX) % 10;
            break;
        case 13:
            digit = ((info->temperature + UINT8_MAX) / 10) % 10;
            break;
        case 14:
            // старшая цифра температуры
            digit = ((info->temperature + UINT8_MAX) / 100) % 10;
            break;
        default:
            break;            
        }
    }
    return digit;
}

// Сортировка данных на основе Radix Sort
// копирование или перемещение элементов не требуется
// 1) последовательно сортируем информационные записи по цифрам (вместо разрядов при сортировке целых чисел),
//    сложность алгоритма линейная O(15*N): 15 - число цифр в каждой записи, N - число записей
// 2) сортируются указатели на элементы списка, а не сами элементы, это сокращает объёмы коприрования
// 3) т.к. структура организована как односвязный список, нет необходимости перемещать элементы,
//    просто, переписываем root и для каждого элмента - указатель на следующий,
// 4) таким образом, при проходе по списку от root получаем уопорядоченный по возрастанию список
ITEM_PTR DataRadixSort(DATA_PTR data, uint8_t date_priority)
{
    const uint8_t num_digits = 15U;
    // партиции - на каждой итерации список элементов, имеющих одинаковую цифру на данной позиции в записи 
    ITEM_PTR partitions[10][data->size];
    ITEM_PTR current = data->root;
    uint32_t item_count = 0;
    ITEM_PTR data_item_pointers[data->size];
    while(current != NULL) {
        if (item_count >= data->size) {
            // ошибочный размер
            return NULL;
        }      
        data_item_pointers[item_count] = current;
        ++item_count;
        current = current->next;
    }
    uint32_t partition_length[10];
    for(uint32_t pos = 0; pos < num_digits; ++pos) {
        // внешний цикл, число проходов -по числу цифр информационной записи
        for (uint8_t row = 0; row < 10; ++row) {
            partition_length[row] = 0;
            for (uint32_t col = 0; col < data->size; ++col) {
                partitions[row][col] = 0;
            }
        }
        for (uint32_t i = 0; i < data->size; ++i) {
            // внутренний цикл, проходим по всему массиву, переносим в партиции указатели на элементы
            // в соответствии с цифрами на текущей позиции в элементах
            uint8_t digit = InfoDigit(&(data_item_pointers[i]->info), pos, date_priority);
            partitions[digit][partition_length[digit]] = data_item_pointers[i];
            partition_length[digit] += 1;
        }
        uint32_t idx = 0;
        // собираем все партиции в один список и продолжаем сортировке по следующей позиции (цифре в записи)
        for (uint8_t row = 0; row < 10; ++row) {
            for (uint32_t col = 0; col < partition_length[row]; ++col) {
                data_item_pointers[idx] = partitions[row][col];
                ++idx;
            }
        }
    }
    // переписываем связи элементов так, чтобы от root они шли по возрастанию
    data->root = data_item_pointers[0];
    // указатели теперь лежат в порядке возрастания данных, просто считываем их все подряд
    current = data->root;
    for (uint32_t i = 1; i < data->size; ++i) {
        current->next = data_item_pointers[i];
        current = current->next;
    }
    // новый последний элемент - последний в массиве отсортированных указателей
    data->last = current;
    data->last->next = NULL;
    return data->root;
}


typedef int64_t (*DateComparator)(Date* date_cmp_1, Date* date_cmp_2, uint32_t* precision,
                                  uint16_t* year, uint8_t* month, float* avg, int8_t* min, int8_t* max);

void TemperatureStatistics(DATA_PTR data, Date* date_cmp_1, Date* date_cmp_2, uint32_t* precision,
                           uint16_t* year, uint8_t* month, float* avg, int8_t* min, int8_t* max)
{
    ITEM_PTR current = data->root;
    int8_t interval_min = INT8_MAX;
    int8_t interval_max = INT8_MIN;
    float interval_sum = 0.0F;
    uint32_t item_count = 0;
    while(current != NULL) {
        uint8_t update_condition = 0;
        Date* current_date = &current->info.date;
        if (date_cmp_1 != NULL && date_cmp_2 != NULL) {
            // интервал дат
            int64_t from_diff = DateDiff(current_date, date_cmp_1, *precision);
            int64_t to_diff = DateDiff(current_date, date_cmp_2, *precision);
            update_condition = (from_diff >= 0) && (to_diff <= 0);
        } else if (date_cmp_1 != NULL && date_cmp_2 == NULL) {
            // точная дата (год + [месяц] + [день] + [час] - задаётся precision)
            int64_t date_diff = DateDiff(current_date, date_cmp_1, *precision);
            update_condition = (date_diff == 0);
        } else if (year != NULL && month == NULL) {
            // конкретный год
            update_condition = (current_date->yyyy == *year);
        } else if (year != NULL && month != NULL) {
            // конкретный месяц  конкретного года
            update_condition = (current_date->yyyy == *year) && (current_date->mo == *month);
        }
        if (update_condition) {
            ++item_count;
            int8_t current_temperature = current->info.temperature;
            if (max != NULL && current_temperature > interval_max) {
                interval_max = current_temperature;
            }
            if (min != NULL && current_temperature < interval_min) {
                interval_min = current_temperature;
            }
            if (avg != NULL) {
                interval_sum += (float)current_temperature;
            }
        }
        current = current->next;
    }
    if (0 == item_count) {
        if (max != NULL) {
            *max = 0;
        }
        if (min != NULL) {
            *min = 0;
        }
        if (avg != NULL) {
            *avg = 0.0F;
        }
    } else {
        if (max != NULL) {
            *max = interval_max;
        }
        if (min != NULL) {
            *min = interval_min;
        }
        if (avg != NULL) {
            *avg = interval_sum / (float)item_count;
        }
    }
}

// Базовая универсальная функция - статистика на произвольном интервале (точность определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void DateIntervalStatics(DATA_PTR data, Date from_date, Date to_date, uint32_t precision,
                         float* avg, int8_t* min, int8_t* max)
{
    TemperatureStatistics(data, &from_date, &to_date, &precision, NULL, NULL, avg, min, max);
}

// Базовая универсальная функция - стастика за указанный год, месяц, день (определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void ExactDateStatics(DATA_PTR data, Date date, uint32_t precision, float* avg, int8_t* min, int8_t* max)
{
    TemperatureStatistics(data, &date, NULL, &precision, NULL, NULL, avg, min, max);
}

// Статистика за конкретный год
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void YearStatistics(DATA_PTR data, uint16_t year, float* avg, int8_t* min, int8_t* max)
{
    TemperatureStatistics(data, NULL, NULL, NULL, &year, NULL, avg, min, max);
}

// Статистика за конкретный месяц конкретного года
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void MonthStatistics(DATA_PTR data, uint16_t year, uint8_t month,
                     float* avg, int8_t* min, int8_t* max)
{
    TemperatureStatistics(data, NULL, NULL, NULL, &year, &month, avg, min, max);
}

uint8_t UniqueYears(DATA_PTR data, uint16_t years[])
{
    if (NULL == data || NULL == data->root) {
        return 0;
    }
    ITEM_PTR current = data->root;
    uint16_t current_year = 0;
    uint32_t years_count = 0;
    while(current != NULL) {
        if (current->info.date.yyyy != current_year) {
            current_year = current->info.date.yyyy;
            years[years_count] = current_year;
            ++years_count;
            
        }
        current = current->next;
    }
    return years_count;
}

uint16_t UniqueMonths(DATA_PTR data, uint16_t years[], uint8_t months[])
{
    if (NULL == data || NULL == data->root) {
        return 0;
    }
    ITEM_PTR current = data->root;
    uint16_t current_year = 0;
    uint8_t current_month = 0;
    uint16_t months_count = 0;
    while(current != NULL) {
        if (current->info.date.yyyy == current_year && current->info.date.mo != current_month) {
            current_year = current->info.date.yyyy;
            current_month = current->info.date.mo;
            months[months_count] = current_month;
            years[months_count] = current_year;
            ++months_count;
            current_month = current->info.date.mo;
        } else if (current->info.date.yyyy != current_year) {
            current_year = current->info.date.yyyy;
            current_month = current->info.date.mo;
            months[months_count] = current_month;
            years[months_count] = current_year;
            ++months_count;            
        }
        current = current->next;
    }
    return months_count;
}

// Статистика по годам
uint8_t PerYearStatistics(DATA_PTR data, StatisticsArrayRecord array[])
{
    uint16_t unique_years[100];
    uint8_t years_count = UniqueYears(data, unique_years);
    for(uint8_t n = 0; n < years_count; ++n) {
        array[n].year = unique_years[n];
        YearStatistics(data, unique_years[n], &array[n].avg, &array[n].min, &array[n].max);
    }
    return years_count;
}

// Статистика по месяцам
uint16_t PerMonthStatistics(DATA_PTR data, StatisticsArrayRecord array[])
{
    uint16_t unique_years[1200];
    uint8_t unique_months[1200];
    uint8_t months_count = UniqueMonths(data, unique_years, unique_months);
    for(uint8_t n = 0; n < months_count; ++n) {
        array[n].year = unique_years[n];
        array[n].month = unique_months[n];
        MonthStatistics(data, unique_years[n], unique_months[n], &array[n].avg, &array[n].min, &array[n].max);
    }
    return months_count;
}

void PrintStatisticsRecord(StatisticsArrayRecord* record)
{
    if (0 == record->month) {
        printf("   %04hu  | %+6.2f | %+6.2f | %+6.2f \n", record->year, (float)record->min, (float)record->max,record->avg);
        printf("---------+--------+--------+--------\n");
    } else {
        printf(" %04hu.%02hu | %+6.2f | %+6.2f | %+6.2f \n", record->year, record->month, (float)record->min, (float)record->max,record->avg);
        printf("---------+--------+--------+--------\n");
    }
}

void PrintStatisticsArray(uint16_t size, StatisticsArrayRecord* array)
{
    if (0 == array[0].month) {
        printf("   год   |  мин.  |  макс. |  сред.  \n");
        printf("---------+--------+--------+--------\n");
    } else {
        printf("год.мес. |  мин.  |  макс. | сред.  \n");
        printf("---------+--------+--------+--------\n");
    }
    for(uint16_t i = 0; i < size; ++i) {
        PrintStatisticsRecord(&array[i]);
    }
}

