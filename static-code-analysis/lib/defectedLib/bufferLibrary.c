#include "bufferLibrary.h"
#include <stdint.h>
#include <stdlib.h>

void dynamic_buffer_overrun_018()
{
    int *buf = (int *)calloc(5, sizeof(int));
    int indexes[4] = {3, 4, 5, 6};
    int index = 4;
    if (buf != NULL)
    {
        *(buf + indexes[index]) = 1; /*Tool should detect this line as error*/ /*ERROR:Buffer overrun*/
        free(buf);
    }
}

void memory_leak_001()
{
    void *x = malloc(1024);
}