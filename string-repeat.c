#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char **str_repeat(char *str, int times)
{
    char **repeats = malloc(times * sizeof (char *));
    while(times--)
    {
        repeats[times] = malloc(strlen(str) + 1);
        strncpy(repeats[times], str, strlen(str));
    }
    return repeats;
}

int main(int argc, char **argv)
{
    char **repeats = str_repeat("fink ployd", 5);
    for (int i = 0; i < 5; i++)
    {
        assert(strlen(repeats[i]) == 10);
        assert(strcmp(repeats[i], "fink ployd") == 0);
        free(repeats[i]);
    }
    free(repeats);
    return 0;
}
