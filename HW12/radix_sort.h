#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <inttypes.h>
#include <stdio.h>

uint8_t DigitsCount(uint64_t n)
{
    uint8_t count = 0U;
    do {
        n /= 10U;
        ++count;
    } while (n != 0);
    return count;
}

void RadixSort(uint32_t size, uint64_t array[])
{
    const uint8_t num_digits = 20U;
    uint64_t base = 10U;

    uint32_t item_length_count[num_digits];
    for (uint32_t i = 0; i < num_digits; ++i) {
        item_length_count[i] = 0;
    }
    for (uint32_t i = 0; i < size; ++i) {
        item_length_count[DigitsCount(array[i])] += 1;
    }
    uint32_t max_length_count = 0;
    for (uint32_t i = 0; i < num_digits; ++i) {
        if (item_length_count[i] > max_length_count) {
            max_length_count = item_length_count[i];
        }
    }

    uint64_t divisor = 1U;
    uint64_t partitions[base][max_length_count];
    uint32_t partition_length[base];
    for(uint32_t pos = 0; pos < num_digits; ++pos) {
        printf("position: %u\n", pos);
        for (uint8_t row = 0; row < base; ++row) {
            partition_length[row] = 0;
            for (uint32_t col = 0; col < max_length_count; ++col) {
                partitions[row][col] = 0;
            }
        }
        for (uint32_t i = 0; i < size; ++i) {
            uint8_t digit = (array[i] / divisor) % base;
            printf("\t%lu : %hhu : %u\n", array[i], digit, partition_length[digit]);
            partitions[digit][partition_length[digit]] = array[i];
            partition_length[digit] += 1;
        }
        uint32_t idx = 0;
        for (uint8_t row = 0; row < base; ++row) {
            if (partition_length[row] > 0) {
                printf("%hhu: [", row);
            }
            for (uint32_t col = 0; col < partition_length[row]; ++col) {
                printf("%lu,", partitions[row][col]);
                array[idx] = partitions[row][col];
                ++idx;
            }
            if (partition_length[row] > 0) {
                printf("]\n");
            }
        }
        divisor *= base;
    }
}

#endif