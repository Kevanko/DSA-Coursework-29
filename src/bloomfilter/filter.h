// filter.h
#pragma once

typedef unsigned int (*HashFunction)(char *, int);

struct BloomFilter;

struct BloomFilter *initializeFilter(int size, int numHashFunctions);
void freeFilter(struct BloomFilter *filter);
_Bool lookup(struct BloomFilter *filter, char *s);
void insert(struct BloomFilter *filter, char *s);

unsigned int h1(char *s, int arrSize);
unsigned int h2(char *s, int arrSize);
unsigned int h3(char *s, int arrSize);
