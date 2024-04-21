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
        .size = 0U
    };
    for(uint32_t i = 0; i < capacity; ++i) {
        data.items[i].info = NULL_INFO;
        //data.items[i].prev = NULL;
        data.items[i].next = NULL;
    }
    return data;
}

// Добавление записи в массив
// Возвращает указатель на добавленный элемент
ITEM_PTR AddTemperatureInfo(DATA_PTR const data, INFO_PTR const info)
{
    if (data->size + 1 > data->capacity) {
        // не удалсь вставить новый элемент, индекс последнего жлемента не изменился
        return NULL;
    }
    if (0U == data->size) {
        data->items[0].info = *info;
        //data->items[0].prev = NULL;
        data->items[0].next = NULL;
        data->root = &(data->items[0]);
        data->last = data->root;
    } else {
        // находим незаполненный элемент
        uint32_t i = 0;
        for(; i < data->capacity; ++i) {
            // if (NULL == data->items[i].prev && NULL == data->items[i].next) {
            //     break;
            // }
            if (NULL == data->items[i].next && data->last != &(data->items[i])) {
                break;
            }
        }
        // записываем информацию
        data->items[i].info = *info;
        //data->items[i].prev = data->last;
        data->items[i].next = NULL;
        // обновляем указатели на последний элемент
        data->last->next = &(data->items[i]);
        data->last = &(data->items[i]);
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
    item->info = NULL_INFO;
    //item->prev = NULL;
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
    //item->prev->next = item->next;
    ITEM_PTR prev = NULL;
    if (item == data->root) {
        data->root = ResetDataItem(item);
    } else {
        prev = PrevDataItem(data, item);
    }
    ITEM_PTR next = ResetDataItem(item);
    if (prev != NULL) {
        prev->next = next;
    }
    if (data->last != item) {
        data->last = next;
    } else {
        data->last = prev;
    }
    data->size -= 1;
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
    while (item != NULL && InfoDiff(&item->info, info, INFO_DP_MINUTE_PRECISION) != 0) {
        item = item->next;
    }
    return RemoveTemperatureInfoByPtr(data, item);
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
            date_str->str, "%04hu.%02hhu.%02hhu|%02hhu:%02hhu",
            NULL_INFO.date.yyyy, NULL_INFO.date.mo, NULL_INFO.date.dd, NULL_INFO.date.hh, NULL_INFO.date.mi);    
    } else {
        sprintf(date_str->str, "%04hu.%02hhu.%02hhu|%02hhu:%02hhu", date->yyyy, date->mo, date->dd, date->hh, date->mi);
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
    DateString ds;
    DateToStr(&info->date, &ds);
    const char* row_delimiter = border ? "\n----------+-----+---" : "";
    if (NULL == info) {
        sprintf(info_str->str, "%s| 00%s", ds.str, row_delimiter);
    } else {
        if (0 == info->temperature) {
            sprintf(info_str->str, "%s| 00%s", ds.str, row_delimiter);
        } else {
            sprintf(info_str->str, "%s|%+02d%s", ds.str, info->temperature, row_delimiter);
        }
    }
}

// Функция сравнения дат с указанием полей для сравнения
// Возвращает -1 (меньше), 0 (равно), 1 (больше)
int64_t DateDiff(Date* date_a, Date* date_b, uint32_t precision)
{
    return (int64_t)DateToInt(date_a, precision) - (int64_t)DateToInt(date_b, precision);
}

// Функция сравнения TemperatureInfo с указанием порядка полей для сортировки
int64_t InfoDiff(INFO_PTR info_a, INFO_PTR info_b, uint64_t date_precision)
{
    return (int64_t)InfoToInt(info_a, date_precision) - (int64_t)InfoToInt(info_b, date_precision);
}

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
// вспомогательная функция сортировки - модияикация Count sort
// копирование или перемещение элементов не требуется
// 1) находим минимальный элемент
// 2) расстояние элемента от минимального равно его индексу в упорядоченном списке
// 3) т.к. структура организована как односвязный список, нет необходимости перемещать элементы,
//    просто, переписываем root и для каждого элмента - указатель на следующий,
// 4) таким образом, при проходе по списку от root получаем уопорядоченный по возрастанию список
void SortTemperatureInfo_(DATA_PTR data, uint64_t date_precision)
{
    // находим элемент с минимальным набором (дата + температура)
    uint64_t min_info_int = UINT64_MAX;
    ITEM_PTR item_ptrs[data->size];
    ITEM_PTR min_info_ptr = NULL;
    uint64_t info_int_values[data->size];
    ITEM_PTR current = data->root;
    uint32_t count = 0;
    while (current != NULL) {
        info_int_values[count] = InfoToInt(&current->info, date_precision);
        printf("__ %u : %lu\n", count, info_int_values[count]);
        item_ptrs[count] = current;
        printf("-> %u : %lu\n", count, min_info_int);
        if (info_int_values[count] < min_info_int) {
            printf(">< %lu _ %lu\n", info_int_values[count], min_info_int);
            min_info_int = info_int_values[count];
            min_info_ptr = current;
        }
        printf("<- %u : %lu\n", count, min_info_int);
        current = current->next;
        count += 1;
    }
    // упорядочиваем указатели на элементы по возрастанию (дата + температура)
    ITEM_PTR sorted_item_ptrs[data->size]; 
    sorted_item_ptrs[0] = min_info_ptr;
    for (uint32_t i = 1; i < data->size; ++i) {
        sorted_item_ptrs[i] = NULL;
    }
    uint32_t offset = 0;   
    for (uint32_t i = 0; i < data->size; ++i) {
        uint64_t info_diff = info_int_values[i] - min_info_int;
        printf(">> %lu, %lu, %lu\n", info_int_values[i], min_info_int, info_diff);
        if (sorted_item_ptrs[info_diff] != NULL) {
            // уже есть такой элемент, кладём следом за ним
            offset += 1;
        }
        sorted_item_ptrs[info_diff + offset] = item_ptrs[i];
    }
    // переписываем связи элементов так, чтобы от root они шли по возрастанию
    data->root = sorted_item_ptrs[0];
    current = data->root;
    for (uint32_t i = 1; i < data->size; ++i) {
        current->next = sorted_item_ptrs[i];
        current = current->next;
    }
    // новый последний элемент - последний в массиве отсортированных указателей
    data->last = sorted_item_ptrs[data->size - 1];
}
// Сортировка массива записей по дате
// Возвращает указатель на новый корневой элемент
ITEM_PTR SortTemperatureInfoByDate(DATA_PTR data)
{
    if (NULL == data || 0 == data->size) {
        return NULL;
    }    
    SortTemperatureInfo_(data, INFO_DP_MINUTE_PRECISION);
    return data->root;
}
// Сортировка массива записей по температуре
// Возвращает указатель на новый корневой элемент
ITEM_PTR SortTemperatureInfoByTemperature(DATA_PTR data)
{
    if (NULL == data || 0 == data->size) {
        return NULL;
    }    
    SortTemperatureInfo_(data, INFO_TP_MINUTE_PRECISION);
    return data->root;
}

// Базова универсальная функция - статистика на произвольном интервале (точность определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void DateIntervalStatics(DATA_PTR data, Date from_date, Date to_date, uint32_t precision,
                         int8_t* avg, int8_t* min, int8_t* max)
{

}

// Базовая универсальная функция - стастика за указанный год, месяц, день (определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void ExactDateStatics(DATA_PTR data, Date date, uint32_t precision, int8_t* avg, int8_t* min, int8_t* max)
{

}

// Статистика за конкретный год
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void YearStatistics(DATA_PTR data, uint16_t year, int8_t* avg, int8_t* min, int8_t* max)
{

}

// Статистика за конкретный месяц
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void MonthStatistics(uint32_t data_size, DATA_PTR data, uint16_t year, uint8_t,
                     int8_t* avg, int8_t* min, int8_t* max)
{

}                     