#include <stdio.h>
#include "list.h"

void rowMajorTest() {
    printf("\nRow major");
    char *d;
    // Allocating a char array for integers with the dimensions 3 * 3
    d = two_d_alloc(3, 3, sizeof(int));
    // Storing the int value 4 on the location x: 1, y: 0
    two_d_store_row(d, 1, 0, sizeof(int), 4);
    // Storing the int value 3 on the location x: 2, y: 0
    two_d_store_row(d, 2, 0, sizeof(int), 3);

    // Using row major mode we can see in the output of the memory
    // dump that all x values are next to each other in memory for
    // each y value
    memoryDump(d, sizeof(int));

    two_d_dealloc(d);
}

void columnMajorTest() {
    printf("\nColumn major");
    char *d;
    // Allocating a char array for integers with the dimensions 3 * 3
    d = two_d_alloc(3, 3, sizeof(int));
    // Storing the int value 4 on the location x: 1, y: 0
    two_d_store_column(d, 1, 0, sizeof(int), 4);
    // Storing the int value 3 on the location x: 2, y: 0
    two_d_store_column(d, 2, 0, sizeof(int), 3);

    // Using column major mode we can see in the output of the memory
    // dump that all y values are next to each other in memory for
    // each x value
    memoryDump(d, sizeof(int));

    two_d_dealloc(d);
}

int main() {
    printf("Memory dump test\n");
    rowMajorTest();
    columnMajorTest();

    return 0;
}