#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <inttypes.h>


typedef struct
{
    uint16_t yyyy; // year
    uint8_t  mo;   // month
    uint8_t  dd;   // day
    uint8_t  hh;   // hours
    uint8_t  mi;   // minutes
} Date;

typedef struct
{
    uint16_t mi:6;
    uint16_t hh:5;
    uint16_t dd:5;
    uint16_t mo:4;
    uint16_t yyyy:12;    
} PackedDate;

typedef struct
{
    uint16_t temperature: 8;
    uint16_t mi:6;
    uint16_t hh:5;
    uint16_t dd:5;
    uint16_t mo:4;
    uint16_t yyyy:12;
} PackedInfoDatePriority;

typedef struct
{
    uint16_t mi:6;
    uint16_t hh:5;
    uint16_t dd:5;
    uint16_t mo:4;
    uint16_t yyyy:12;
    uint16_t temperature: 8;
} PackedInfoTemperaturePriority;

typedef union 
{
    PackedDate date;
    uint32_t long_word;
} DateUnion;

typedef struct 
{
    Date   date;
    int8_t temperature;
} TemperatureInfo;

typedef union
{
    PackedInfoDatePriority info;
    uint64_t long_long_word;
} InfoUnionDatePriority;

typedef union
{
    PackedInfoTemperaturePriority info;
    uint64_t long_long_word;
} InfoUnionTemperaturePriority;

typedef struct TemperatureDataItem TemperatureDataItem;
struct TemperatureDataItem
{
    TemperatureInfo info; // данные
    //struct TemperatureDataItem* prev;// указатель на предыдующий элемент
    TemperatureDataItem* next;// указатель на следующий элемент
};

typedef struct 
{
    TemperatureDataItem* items; // указатель на массив элементов
    TemperatureDataItem* root;  // указатель на корневой элемент
    TemperatureDataItem* last;  // указатель на последний добавленный элемент
    uint32_t capacity;          // ёмкость массива, максимально возможное число элементов
    uint32_t size;              // реальный размер массива - число элементов, содержащих полезную информацию
} TemperatureData;

typedef TemperatureInfo* INFO_PTR;
typedef TemperatureDataItem* ITEM_PTR;
typedef TemperatureData* DATA_PTR;

static const uint32_t DATE_YEAR_MASK   = 0b11111111111100000000000000000000;
static const uint32_t DATE_MONTH_MASK  = 0b00000000000011110000000000000000;
static const uint32_t DATE_DAY_MASK    = 0b00000000000000001111100000000000;
static const uint32_t DATE_HOUR_MASK   = 0b00000000000000000000011111000000;
static const uint32_t DATE_MINUTE_MASK = 0b00000000000000000000000000111111;
static const uint32_t DATE_YEAR_PRECISION   = DATE_YEAR_MASK;
static const uint32_t DATE_MONTH_PRECISION  = DATE_YEAR_PRECISION  | DATE_MONTH_MASK;
static const uint32_t DATE_DAY_PRECISION    = DATE_MONTH_PRECISION | DATE_DAY_MASK;
static const uint32_t DATE_HOUR_PRECISION   = DATE_DAY_PRECISION   | DATE_HOUR_MASK;
static const uint32_t DATE_MINUTE_PRECISION = DATE_HOUR_PRECISION  | DATE_MINUTE_MASK;

static const uint64_t INFO_DP_YEAR_MASK   = 0b1111111111110000000000000000000000000000;
static const uint64_t INFO_DP_MONTH_MASK  = 0b0000000000001111000000000000000000000000;
static const uint64_t INFO_DP_DAY_MASK    = 0b0000000000000000111110000000000000000000;
static const uint64_t INFO_DP_HOUR_MASK   = 0b0000000000000000000001111100000000000000;
static const uint64_t INFO_DP_MINUTE_MASK = 0b0000000000000000000000000011111100000000;
static const uint64_t INFO_DP_YEAR_PRECISION   = INFO_DP_YEAR_MASK;
static const uint64_t INFO_DP_MONTH_PRECISION  = INFO_DP_YEAR_PRECISION  | INFO_DP_MONTH_MASK;
static const uint64_t INFO_DP_DAY_PRECISION    = INFO_DP_MONTH_PRECISION | INFO_DP_DAY_MASK;
static const uint64_t INFO_DP_HOUR_PRECISION   = INFO_DP_DAY_PRECISION   | INFO_DP_HOUR_MASK;
static const uint64_t INFO_DP_MINUTE_PRECISION = INFO_DP_HOUR_PRECISION  | INFO_DP_MINUTE_MASK;

static const uint64_t INFO_TP_YEAR_MASK   = 0b0000000011111111111100000000000000000000;
static const uint64_t INFO_TP_MONTH_MASK  = 0b0000000000000000000011110000000000000000;
static const uint64_t INFO_TP_DAY_MASK    = 0b0000000000000000000000001111100000000000;
static const uint64_t INFO_TP_HOUR_MASK   = 0b0000000000000000000000000000011111000000;
static const uint64_t INFO_TP_MINUTE_MASK = 0b0000000000000000000000000000000000111111;
static const uint64_t INFO_TP_YEAR_PRECISION   = INFO_TP_YEAR_MASK;
static const uint64_t INFO_TP_MONTH_PRECISION  = INFO_TP_YEAR_PRECISION  | INFO_TP_MONTH_MASK;
static const uint64_t INFO_TP_DAY_PRECISION    = INFO_TP_MONTH_PRECISION | INFO_TP_DAY_MASK;
static const uint64_t INFO_TP_HOUR_PRECISION   = INFO_TP_DAY_PRECISION   | INFO_TP_HOUR_MASK;
static const uint64_t INFO_TP_MINUTE_PRECISION = INFO_TP_HOUR_PRECISION  | INFO_TP_MINUTE_MASK;

typedef struct
{
    char str[18];
} DateString;

typedef struct
{
    char str[44];
} InfoString;

#endif