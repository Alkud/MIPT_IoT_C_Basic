#ifndef TEMP_API_H
#define TEMP_API_H

#include "data_types.h"


static const TemperatureInfo NULL_INFO = {
    .date = {
        .yyyy = 0U,
        .mo = 0U,
        .dd = 0U,
        .hh = 0U,
        .mi = 0U
    },
    .temperature = 0U
};

uint32_t DateToInt(Date* date, uint32_t precision);
void IntToDate(uint32_t int_value, Date* date, uint32_t precision);


void DateToStr(Date* date, DateString* date_str);

uint64_t InfoToInt(TemperatureInfo* info, uint64_t date_precision);


void InfoToStr(TemperatureInfo* info, InfoString* info_str, uint8_t border);

void PrintInfo(TemperatureInfo* info, uint8_t border);

void PrintData(DATA_PTR data, ITEM_PTR first_item, Date* start_date, uint32_t* date_precision,
               uint32_t* num_items, uint8_t border);

void PrintDataHead(DATA_PTR data, uint32_t* num_items, uint8_t border);
void PrintDataTail(DATA_PTR data, uint32_t* num_items, uint8_t border);

// Создание массива TemperatureInfo
// Возвращает структуру с массивом элементов и служебными данными
TemperatureData CreateTemperatureData(uint32_t capacity, const ITEM_PTR zero_item);

// Добавление записи в массив
// Возвращает указатель на добавленный элемент
ITEM_PTR AddTemperatureInfo(DATA_PTR data, INFO_PTR info);

// Сброс элемента массива
ITEM_PTR ResetDataItem(ITEM_PTR item);

// Удаление записи из массива по указателю на элемент
// Возвращает указатель на элемент, следующий за удалённым
ITEM_PTR RemoveTemperatureInfoByPtr(DATA_PTR data, ITEM_PTR item);

// Удаление записи из массива по значению элемента
// Возвращает указатель на элемент, следующий за удалённым
ITEM_PTR RemoveTemperatureInfoByValue(DATA_PTR data, INFO_PTR info);

// Функция сравнения дат с указанием полей для сравнения
// Возвращает -1 (меньше), 0 (равно), 1 (больше)
int64_t DateDiff(Date* date_a, Date* date_b, uint32_t precision);

// Функция сравнения TemperatureInfo с указанием порядка полей  (приоритет температуры / даты)
int64_t InfoDiff(INFO_PTR info_a, INFO_PTR info_b, uint64_t date_precision);

ITEM_PTR DataRadixSort(DATA_PTR data, uint8_t date_priority);

// Базова универсальная функция - статистика на произвольном интервале (точность определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void DateIntervalStatics(DATA_PTR data, Date from_date, Date to_date, uint32_t precision,
                         float* avg, int8_t* min, int8_t* max);

// Базовая универсальная функция - стастика за указанный год, месяц, день (определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void ExactDateStatics(DATA_PTR data, Date date, uint32_t precision, float* avg, int8_t* min, int8_t* max);

// Статистика за конкретный год
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void YearStatistics(DATA_PTR data, uint16_t year, float* avg, int8_t* min, int8_t* max);

// Статистика за конкретный месяц
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void MonthStatistics(DATA_PTR data, uint16_t year, uint8_t month,
                     float* avg, int8_t* min, int8_t* max);

typedef struct {
    uint16_t year;
    uint8_t month;
    float avg;
    int8_t min; 
    int8_t max;
} StatisticsArrayRecord;

uint8_t UniqueYears(DATA_PTR data, uint16_t years[]);
uint16_t UniqueMonths(DATA_PTR data, uint16_t years[], uint8_t months[]);

// Статистика по годам
uint8_t PerYearStatistics(DATA_PTR data, StatisticsArrayRecord array[]);

// Статистика по месяцам
uint16_t PerMonthStatistics(DATA_PTR data, StatisticsArrayRecord array[]);

void PrintStatisticsRecord(StatisticsArrayRecord* record);

void PrintStatisticsArray(uint16_t size, StatisticsArrayRecord* array);

#endif                     