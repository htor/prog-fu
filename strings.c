#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char **str_repeat(char *str, int times)
{
    int length = strlen(str);
    char **repeats = malloc((times + 1) * sizeof(char *));
    for (int i = 0; i < times; i++)
    {
        repeats[i] = malloc(length + 1);
        strcpy(repeats[i], str);
    }
    repeats[times] = NULL;
    return repeats;
}

int main(int argc, char **argv)
{
    char *str = "herman";
    char **repeats = str_repeat(str, 11);
    char **start = repeats;
    int pcount = 0;
    for (int i; i < 11; i++)
    {
        assert(strcmp(repeats[i], str) == 0); 
        assert(repeats[i] != str); 
        free(repeats[i]);
    }
    assert(repeats[11] == NULL);
    free(start);
    return 0;
}
