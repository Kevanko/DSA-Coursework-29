#include <stdbool.h>

#include <bloomfilter/filter.h>

// Driver Code
int main()
{
    _Bool bitarray[100] = {false};
    int arrSize = 100;
    char *sarray[33] = {"abound", "abounds", "abundance",
                        "abundant", "accessible", "bloom",
                        "blossom", "bolster", "bonny",
                        "bonus", "bonuses", "coherent",
                        "cohesive", "colorful", "comely",
                        "comfort", "gems", "generosity",
                        "generous", "generously", "genial",
                        "bluff", "cheater", "hate",
                        "war", "humanity", "racism",
                        "hurt", "nuke", "gloomy",
                        "facebook", "geeksforgeeks", "twitter"};
    for (int i = 0; i < 33; i++)
    {
        insert(bitarray, arrSize, sarray[i]);
    }
    return 0;
}