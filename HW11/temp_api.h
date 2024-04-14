#include <inttypes.h>


struct TemperatureInfo
{
    uint16_t yyyy;
    uint8_t  mm;
    uint8_t  dd;
    uint8_t  hh;
    uint8_t  mi;
    int8_t   temperature;
};

struct Date
{
    uint16_t yyyy;
    uint8_t  mm;
    uint8_t  dd;
    uint8_t  hh;
    uint8_t  mi;
};

const struct Date NULL_DATE = {
    .yyyy = 0U,
    .mm = 0U,
    .dd = 0U,
    .hh = 0U,
    .mi = 0U
};

// Флаги сравнения элементов даты 
const uint8_t CHECK_YEAR  = 0b1000U;
const uint8_t CHECK_MONTH = 0b0100U;
const uint8_t CHECK_DAY   = 0b0010U;
const uint8_t CHECK_HOUR  = 0b0001U;

// Функция сравнения дат с указанием полей для сравнения
int DateComparator(struct Date* date_a, struct Date* date_b, int check_year, int check, uint8_t check_flags);

// Базова универсальная функция - статистика на произвольном интервале
void DateIntervalStatics(uint32_t data_size, struct TemperatureInfo data[], struct Date from_date,
                                    struct Date to_date, int8_t* avg, int8_t* min, int8_t* max);

// Базовая универсальная функция - стастика за указанный год, месяц, час
void ExactDateStatics(uint32_t data_size, struct TemperatureInfo data[], struct Date date,
                                        int8_t* avg, int8_t* min, int8_t* max);                                          

// Статистика за конкретный год
void YearStatistics(uint32_t data_size, struct TemperatureInfo data[], uint16_t year,
                    int8_t* avg, int8_t* min, int8_t* max);

// Статистика за конкретный месяц
void MonthStatistics(uint32_t data_size, struct TemperatureInfo data[], uint16_t year, uint8_t,
                     int8_t* avg, int8_t* min, int8_t* max);