// filter.c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "bloomfilter/filter.h"

struct BloomFilter
{
  _Bool *bitarray;
  int arrSize;
  HashFunction *hashFunctions;
  int numHashFunctions;
};

// Инициализация фильтра Блума
struct BloomFilter *initializeFilter(int size, int numHashFunctions)
{
  struct BloomFilter *filter = (struct BloomFilter *)malloc(sizeof(struct BloomFilter));
  filter->bitarray = (_Bool *)calloc(size, sizeof(_Bool));
  filter->arrSize = size;
  filter->numHashFunctions = numHashFunctions;
  filter->hashFunctions = (HashFunction *)malloc(numHashFunctions * sizeof(HashFunction));

  // Инициализация хэш-функций
  if (numHashFunctions >= 1)
    filter->hashFunctions[0] = &h1;
  if (numHashFunctions >= 2)
    filter->hashFunctions[1] = &h2;
  if (numHashFunctions >= 3)
    filter->hashFunctions[2] = &h3;

  return filter;
}

// Освобождение ресурсов фильтра Блума
void freeFilter(struct BloomFilter *filter)
{
  free(filter->bitarray);
  free(filter->hashFunctions);
  free(filter);
}

// lookup operation
_Bool lookup(struct BloomFilter *filter, char *s)
{
  for (int i = 0; i < filter->numHashFunctions; i++)
  {
    int index = filter->hashFunctions[i](s, filter->arrSize);
    if (!filter->bitarray[index])
      return false;
  }
  return true;
}

// insert operation
void insert(struct BloomFilter *filter, char *s)
{
  for (int i = 0; i < filter->numHashFunctions; i++)
  {
    int index = filter->hashFunctions[i](s, filter->arrSize);
    filter->bitarray[index] = true;
  }
}

/*fnv1Hash*/
unsigned int h1(char *str, int arrSize)
{
  unsigned int hash = 2166136261U;
  for (int i = 0; str[i] != '\0'; i++)
  {
    hash = (hash * 16777619) ^ str[i];
  }
  return hash % arrSize;
}
/*fnv1aHash*/
unsigned int h2(char *str, int arrSize)
{
  unsigned int hash = 2166136261U;
  for (int i = 0; str[i] != '\0'; i++)
  {
    hash ^= str[i];
    hash = (hash * 16777619);
  }
  return hash % arrSize;
}

/*djb2Hash*/
unsigned int h3(char *str, int arrSize)
{
  unsigned int hash = 5381;
  int c;
  while ((c = *str++))
  {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash % arrSize;
}
