#ifndef CSV_READER_H
#define CSV_READER_H

#include <stdio.h>
#include <inttypes.h>

#define STR_(x) #x
#define STR(x) STR_(x)

// YYYY;MO;DD;HH;MI;TTT\n
#define APPROX_STRING_LENGTH 21

#define BAD_ROW (-2)


typedef struct
{
    char file_name[FILENAME_MAX];
    FILE* handle;
    uint32_t approx_data_size;
    char buffer[2 * APPROX_STRING_LENGTH];
    uint32_t rows_read;
    char c_yyyy[15];
    char c_mo[15];
    char c_dd[15];
    char c_hh[15];
    char c_mi[15];
    char c_ttt[15];
    int i_yyyy;
    int i_mo;
    int i_dd;
    int i_hh;
    int i_mi;
    int i_ttt;
} CsvFileDescriptor;

uint32_t EstimateDataSize(const char* file_name);

int OpenFile(CsvFileDescriptor* descriptor);

void CloseFile(CsvFileDescriptor* descriptor);

int ParseCsvRow(CsvFileDescriptor* descriptor);

int CheckBuffer(CsvFileDescriptor* descriptor);

int GetNextRow(CsvFileDescriptor* descriptor);

#endif