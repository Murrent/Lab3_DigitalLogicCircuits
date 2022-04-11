#include <stdio.h>
#include "list.h"

void rowMajorTest() {
    printf("Row major test\n");
    char *d;
    int y;
    // Allocating a char array for integers with the dimensions 20 * 50
    d = two_d_alloc(20, 50, sizeof(int));
    // Storing the value 4 at the location x: 12, y: 42 in row major mode
    two_d_store_row(d, 12, 42, sizeof(int), 4);
    // Storing the value 3 at the location x: 10, y: 15 in row major mode
    two_d_store_row(d, 10, 15, sizeof(int), 3);
    // Fetching the same values in row major mode and adding them together
    y = two_d_fetch_row(d, 12, 42, sizeof(int)) + two_d_fetch_row(d, 10, 15, sizeof(int));

    printf("y = %d\n", y);
    // Deallocating the array
    two_d_dealloc(d);
}
void columnMajorTest() {
    printf("Column major test\n");
    char *d;
    int y;
    // Allocating a char array for integers with the dimensions 20 * 50
    d = two_d_alloc(20, 50, sizeof(int));
    // Storing the value 4 at the location x: 12, y: 42 in column major mode
    two_d_store_column(d, 12, 42, sizeof(int), 4);
    // Storing the value 3 at the location x: 10, y: 15 in column major mode
    two_d_store_column(d, 10, 15, sizeof(int), 3);
    // Fetching the same values in column major mode and adding them together
    y = two_d_fetch_column(d, 12, 42, sizeof(int)) + two_d_fetch_column(d, 10, 15, sizeof(int));

    printf("y = %d\n", y);
    // Deallocating the array
    two_d_dealloc(d);
}
int main() {
    rowMajorTest();
    columnMajorTest();

    return 0;
}
