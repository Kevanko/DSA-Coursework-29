#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bloomfilter/filter.h"

#define NUM_ELEMENTS 1000000
#define OUTPUT_INTERVAL 100000
#define MAX_STRING_LENGTH 6

char **generateStrings()
{
    char **result = malloc(sizeof(char *) * NUM_ELEMENTS);
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        result[i] = malloc(sizeof(char) * (MAX_STRING_LENGTH + 1));
        int tmp = i;
        for (int j = 0; j < MAX_STRING_LENGTH; j++)
        {
            if (tmp > 0)
            {
                result[i][j] = 'A' + tmp % 26;
                tmp /= 26;
            }
            else
                result[i][j] = 'A';
        }
        result[i][MAX_STRING_LENGTH] = '\0';
    }
    return result;
}

void freeStrings(char **str)
{
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        free(str[i]);
    }
    free(str);
}

int main()
{
    int arrSize = 10000000;
    char **strings = generateStrings();
    int numHashFunctions = 3;
    int falsePositives = 0;
    int dt = 1E6;

    struct BloomFilter *filter = initializeFilter(arrSize, numHashFunctions);

    clock_t start, end;
    double cpu_time_used;

    printf("Time of lookup\t\tFalse Positives\n");

    for (int i = 1; i <= NUM_ELEMENTS; i++)
    {
        end = 0;
        if (i % OUTPUT_INTERVAL == 0)
        {
            start = clock();
            for (int k = 0; k < dt; k++)
            {
                lookup(filter, strings[i - 1]);
            }
            end = clock() - start;
        }
        falsePositives += lookup(filter, strings[i - 1]);
        insert(filter, strings[i - 1]);
        if (i % OUTPUT_INTERVAL == 0)
        {
            cpu_time_used = ((double)(end)) / CLOCKS_PER_SEC / dt;
            printf("%.12f ", cpu_time_used);
            printf("\t\t\t%d\n", falsePositives);
        }
    }

    freeFilter(filter);
    freeStrings(strings);
    return 0;
}
