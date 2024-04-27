#include "csv_reader.h"

#include <string.h>

uint32_t EstimateDataSize(const char* file_name)
{
    FILE* fp = fopen(file_name, "r"); 
  
    if (fp == NULL) {
        return 0; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
    uint64_t last_position = ftell(fp); 
    fclose(fp); 
  
    return last_position / APPROX_STRING_LENGTH;     
}

int OpenFile(CsvFileDescriptor* descriptor)
{
    descriptor->approx_data_size = EstimateDataSize(descriptor->file_name);
    descriptor->handle = fopen(descriptor->file_name, "r");
    if (NULL == descriptor->handle) {
        return -1;
    }
    descriptor->rows_read = 0;
    return 0;
}

void CloseFile(CsvFileDescriptor* descriptor)
{
    if (descriptor->handle != NULL) {
        fclose(descriptor->handle);
    }
    descriptor->approx_data_size = 0;
    descriptor->rows_read = 0;
    descriptor->handle = NULL;
}

int ParseCsvRow(CsvFileDescriptor* descriptor)
{
    int num_items = 0;
    uint8_t item_begin = 0;
    uint8_t read_pos = 0;
    uint8_t dest_pos = 0;
    char c;
    char* dest;
    do {
        c = descriptor->buffer[read_pos];
        switch (num_items)
        {
        case 0:
            dest = descriptor->c_yyyy;
            break;
        case 1:
            dest = descriptor->c_mo;
            break;
        case 2:
            dest = descriptor->c_dd;
            break;
        case 3:
            dest = descriptor->c_hh;
            break;
        case 4:
            dest = descriptor->c_mi;
            break;
        case 5:
            dest = descriptor->c_ttt;
            break;
        default:
            break;
        }
        if ((c >= '0' && c <= '9') || (c == '-' || c == '+')) {
            if ((c == '-' || c == '+') && num_items != 5) {
                return num_items;
            }    
            dest[dest_pos] = c;
            ++dest_pos;
        } else if (';' == c || '\n' == c || '\r' == c || '\0' == c) {
            dest[dest_pos] = '\0';
            ++num_items;
            dest_pos = 0;
        } else if (c != ' '){
            // недопустимые символы
            return num_items;
        }
        ++read_pos;
    } while (num_items < 6 && c != '\n' && c != '\r' && c !='\0');
    if (c != '\n' && c != '\r' && c != '\0') {
        ++num_items;
    }
    return num_items;
}

int CheckBuffer(CsvFileDescriptor* descriptor)
{
    int num_items = ParseCsvRow(descriptor);
    if (num_items != 6) {
        return BAD_ROW;
    }
    num_items = 0;
    if (sscanf(descriptor->c_yyyy, "%d", &descriptor->i_yyyy) != 1) {
        return BAD_ROW;
    }
    ++num_items;
    if (sscanf(descriptor->c_mo, "%d", &descriptor->i_mo) != 1) {
        return BAD_ROW;
    }    
    ++num_items;
    if (sscanf(descriptor->c_dd, "%d", &descriptor->i_dd) != 1) {
        return BAD_ROW;
    }
    ++num_items;
    if (sscanf(descriptor->c_hh, "%d", &descriptor->i_hh) != 1) {
        return BAD_ROW;
    }
    ++num_items;
    if (sscanf(descriptor->c_mi, "%d", &descriptor->i_mi) != 1) {
        return BAD_ROW;
    }
    ++num_items;
    if (sscanf(descriptor->c_ttt, "%d", &descriptor->i_ttt) != 1) {
        return BAD_ROW;
    }
    ++num_items;
    if (num_items != 6) {
        return BAD_ROW;
    }
    if (descriptor->i_mo > 12) {
        return BAD_ROW;
    }
    if (descriptor->i_dd > 31) {
        return BAD_ROW;
    }
    if (descriptor->i_hh > 24) {
        return BAD_ROW;
    }
    if (descriptor->i_mi > 59) {
        return BAD_ROW;
    }
    if (descriptor->i_ttt < -100 || descriptor->i_ttt > 100) {
        return BAD_ROW;
    }
    return 0;
}

int GetNextRow(CsvFileDescriptor* descriptor)
{
    if (fgets(descriptor->buffer, sizeof descriptor->buffer, descriptor->handle) == NULL) {
        return EOF;
    }
    int check_result = CheckBuffer(descriptor);
    if (check_result != BAD_ROW) {
        descriptor->rows_read += 1;
    }
    return check_result;
}