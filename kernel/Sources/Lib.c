#include "Lib.h"

size_t StringLength(const char *String)
{
    size_t Length = 0;
    while (String[Length])
        Length++;
    return Length;
}
