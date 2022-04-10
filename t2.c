#include <stdio.h>
#include "list.h"

void rowMajorTest() {
    printf("\nRow major");
    char *d;
    d = two_d_alloc(3, 3, sizeof(int));
    two_d_store_row(d, 1, 0, sizeof(int), 4);
    two_d_store_row(d, 2, 0, sizeof(int), 3);

    memoryDump(d, sizeof(int));

    two_d_dealloc(d);
}

void columnMajorTest() {
    printf("\nColumn major");
    char *d;
    d = two_d_alloc(3, 3, sizeof(int));
    two_d_store_column(d, 1, 0, sizeof(int), 4);
    two_d_store_column(d, 2, 0, sizeof(int), 3);

    memoryDump(d, sizeof(int));

    two_d_dealloc(d);
}

int main() {
    printf("Memory dump test\n");
    rowMajorTest();
    columnMajorTest();

    return 0;
}