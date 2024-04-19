#include <stdlib.h>
#include "temp_api.h"



// Создание массива TemperatureInfo
// Возвращает структуру с массивом элементов и служебными данными
struct TemperatureData CreateTemperatureData(const uint32_t capacity, const ITEM_PTR zero_item)
{
    struct TemperatureData data = {
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
INFO_PTR AddTemperatureInfo(DATA_PTR const data, INFO_PTR const info)
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

// Удаление записи из массива
// Возвращает указатель на элемент, следующий за удалённым
INFO_PTR RemoveTemperatureInfo(DATA_PTR data, ITEM_PTR item)
{
    if (NULL == data || NULL == item || 0 == data->size) {
        return NULL;
    }
    //item->prev->next = item->next;
    ITEM_PTR prev = PrevDataItem(data, item);
    ITEM_PTR next = ResetDataItem(item);
    prev->next = next;
    if (data->last != item) {
        data->last = next;
    }
    data->size -= 1;
    return next;
}

// Сортировка массива записей по дате
// Возвращает указатель на новый корневой элемент
INFO_PTR SortTemperatureInfoByDate(DATA_PTR data)
{
    if (NULL == data || 0 == data->size) {
        return NULL;
    }

}


uint32_t DateToInt(struct Date date)
{
    uint32_t result = 0U;
    result  = date.yyyy * YEAR_FACTOR;
    result += date.mo   * MONTH_FACTOR;
    result += date.dd   * DAY_FACTOR;
    result += date.hh   * HOUR_FACTOR;
    result += date.mi   * MINUTE_FACTOR;
    return result;
}

// Функция сравнения дат с указанием полей для сравнения
// Возвращает -1 (меньше), 0 (равно), 1 (больше)
int DateComparator(struct Date* date_a, struct Date* date_b, uint32_t cmp_factor)
{
    return DateToInt(*date_a) / cmp_factor - DateToInt(*date_b) / cmp_factor;
}

void SwapDataItems(ITEM_PTR a, ITEM_PTR b)
{
    a->
}

// Сортировка массива записей по дате
// Возвращает указатель на новый корневой элемент
INFO_PTR SortTemperatureInfoByTemperature(DATA_PTR data)
{
    if (NULL == data || 0 == data->size) {
        return NULL;
    }

}

// Базова универсальная функция - статистика на произвольном интервале (точность определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void DateIntervalStatics(uint32_t data_size, struct TemperatureInfo data[], struct Date from_date,
                         struct Date to_date, uint8_t check_flag, int8_t* avg, int8_t* min, int8_t* max);

// Базовая универсальная функция - стастика за указанный год, месяц, день (определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void ExactDateStatics(uint32_t data_size, struct TemperatureInfo data[], struct Date date, uint8_t check_flags,
                      int8_t* avg, int8_t* min, int8_t* max);                                          

// Статистика за конкретный год
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void YearStatistics(uint32_t data_size, struct TemperatureInfo data[], uint16_t year,
                    int8_t* avg, int8_t* min, int8_t* max);

// Статистика за конкретный месяц
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void MonthStatistics(uint32_t data_size, struct TemperatureInfo data[], uint16_t year, uint8_t,
                     int8_t* avg, int8_t* min, int8_t* max);