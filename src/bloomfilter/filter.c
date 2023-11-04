#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <bloomfilter/filter.h>

#define ll long long

// hash 1
int h1(char *s, int arrSize)
{
  ll int hash = 0;
  for (int i = 0; s[i] != '\0'; i++)
  {
    hash = (hash + ((int)s[i]));
    hash = hash % arrSize;
  }
  return hash;
}

// hash 2
int h2(char *s, int arrSize)
{
  ll int hash = 1;
  for (int i = 0; s[i] != '\0'; i++)
  {
    hash = hash + pow(19, i) * s[i];
    hash = hash % arrSize;
  }
  return hash % arrSize;
}

// hash 3
int h3(char *s, int arrSize)
{
  ll int hash = 7;
  for (int i = 0; s[i] != '\0'; i++)
  {
    hash = (hash * 31 + s[i]) % arrSize;
  }
  return hash % arrSize;
}

// hash 4
int h4(char *s, int arrSize)
{
  ll int hash = 3;
  int p = 7;
  for (int i = 0; s[i] != '\0'; i++)
  {
    hash += hash * 7 + s[0] * pow(p, i);
    hash = hash % arrSize;
  }
  return hash;
}

// lookup operation
_Bool lookup(_Bool *bitarray, int arrSize, char *s)
{
  int a = h1(s, arrSize);
  int b = h2(s, arrSize);
  int c = h3(s, arrSize);
  int d = h4(s, arrSize);

  if (bitarray[a] && bitarray[b] && bitarray && bitarray[c] && bitarray[d])
    return true;
  else
    return false;
}

// insert operation
void insert(_Bool *bitarray, int arrSize, char *s)
{
  // check if the element in already present or not
  if (lookup(bitarray, arrSize, s))
    printf(" %s is Probably already present\n", s);
  else
  {
    int a = h1(s, arrSize);
    int b = h2(s, arrSize);
    int c = h3(s, arrSize);
    int d = h4(s, arrSize);

    bitarray[a] = true;
    bitarray[b] = true;
    bitarray[c] = true;
    bitarray[d] = true;
    printf(" %s inserted\n", s);
  }
}
