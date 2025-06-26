#include <stdio.h>

int PrintError(const char* str)
{
    fprintf(stderr, "%s\n", str);
    return -1;
}
