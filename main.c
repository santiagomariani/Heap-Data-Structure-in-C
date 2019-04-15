#include "heap.h"
#include "testing.h"
#include <stdio.h>

void pruebas_heap(void);

int main(void) {
    pruebas_heap();

    return failure_count() > 0;
}
