#include <stdlib.h>
#include <stdint.h>
#include "module.h"
#include "console.h"
#define ALLOCSIZE 16 * sizeof(float) * 1024 * 512

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

void *malloc(size_t size)
{
    if (allocbuf + ALLOCSIZE - allocp >= size) {
        // console_log("before: %u + %u", (uintptr_t)allocp, size);
        allocp += size;
        // console_log("allocp2: %u", (uintptr_t)allocp);
        return (void *) allocp - size;
    } else {
        return NULL;
    }
}

export void free(void *p)
{
    char *q = (char *)p;
    if (q >= allocbuf && q < allocbuf + ALLOCSIZE)
        allocp = q;
}
