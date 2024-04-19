#include <inttypes.h>


struct TemperatureInfo
{
    uint16_t yyyy; // year
    uint8_t  mo;   // month
    uint8_t  dd;   // day
    uint8_t  hh;   // hours
    uint8_t  mi;   // minutes
    int8_t   temperature;
};

struct Date
{
    uint16_t yyyy;
    uint8_t  mo;
    uint8_t  dd;
    uint8_t  hh;
    uint8_t  mi;
};

const struct TemperatureInfo NULL_INFO = {
    .yyyy = 0U,
    .mo = 0U,
    .dd = 0U,
    .hh = 0U,
    .mi = 0U,
    .temperature = 0U
};

struct TemperatureDataItem
{
    struct TemperatureInfo info; // данные
    //struct TemperatureDataItem* prev;// указатель на предыдующий элемент
    struct TemperatureDataItem* next;// указатель на следующий элемент
};

struct TemperatureData
{
    struct TemperatureDataItem* items; // указатель на массив элементов
    struct TemperatureDataItem* root;  // указатель на корневой элемент
    struct TemperatureDataItem* last;  // указатель на последний добавленный элемент
    uint32_t capacity;                 // ёмкость массива, максимально возможное число элементов
    uint32_t size;                     // реальный размер массива - число элементов, содержащих полезную информацию
};

typedef struct TemperatureInfo* INFO_PTR;
typedef struct TemperatureDataItem* ITEM_PTR;
typedef struct TemperatureData* DATA_PTR;

// Флаги сравнения элементов даты
const uint32_t MINUTE_FACTOR = 1U;
const uint32_t HOUR_FACTOR   = MINUTE_FACTOR * 100U;
const uint32_t DAY_FACTOR    = HOUR_FACTOR * 100U;
const uint32_t MONTH_FACTOR  = DAY_FACTOR * 100U;
const uint32_t YEAR_FACTOR   = MONTH_FACTOR * 100U;

uint32_t DateToInt(struct Date date);

// Создание массива TemperatureInfo
// Возвращает структуру с массивом элементов и служебными данными
struct TemperatureData CreateTemperatureData(uint32_t capacity, const ITEM_PTR zero_item);

// Добавление записи в массив
// Возвращает указатель на добавленный элемент
INFO_PTR AddTemperatureInfo(DATA_PTR data, INFO_PTR info);

// Сброс элемента массива
void ResetDataItem(ITEM_PTR item);

// Удаление записи из массива
// Возвращает указатель на элемент, следующий за удалённым
INFO_PTR RemoveTemperatureInfo(DATA_PTR data, ITEM_PTR item);

// Сортировка массива записей по дате
// Возвращает указатель на новый корневой элемент
INFO_PTR SortTemperatureInfoByDate(DATA_PTR data);

// Сортировка массива записей по дате
// Возвращает указатель на новый корневой элемент
INFO_PTR SortTemperatureInfoByTemperature(DATA_PTR data);

// Функция сравнения дат с указанием полей для сравнения
// Возвращает -1 (меньше), 0 (равно), 1 (больше)
int DateComparator(struct Date* date_a, struct Date* date_b, uint32_t cmp_factor);

// Базова универсальная функция - статистика на произвольном интервале (точность определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void DateIntervalStatics(uint32_t data_size, struct TemperatureInfo data[], struct Date from_date,
                         struct Date to_date, uint32_t cmp_factor, int8_t* avg, int8_t* min, int8_t* max);

// Базовая универсальная функция - стастика за указанный год, месяц, день (определяется флагами сравнения элементов дат)
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void ExactDateStatics(uint32_t data_size, struct TemperatureInfo data[], struct Date date, uint32_t date_items,
                      int8_t* avg, int8_t* min, int8_t* max);                                          

// Статистика за конкретный год
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void YearStatistics(uint32_t data_size, struct TemperatureInfo data[], uint16_t year,
                    int8_t* avg, int8_t* min, int8_t* max);

// Статистика за конкретный месяц
// Записывает по требованию значения маскимального, среднего и минимального значения при ненулевых указателях
void MonthStatistics(uint32_t data_size, struct TemperatureInfo data[], uint16_t year, uint8_t,
                     int8_t* avg, int8_t* min, int8_t* max);