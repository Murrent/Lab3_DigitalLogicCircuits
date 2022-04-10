#include <stdio.h>
#include "list.h"

void rowMajorTest() {
    printf("Row major test\n");
    char *d;
    int y;
    d = two_d_alloc(20, 50, sizeof(int));
    two_d_store_row(d, 12, 42, sizeof(int), 4);
    two_d_store_row(d, 10, 15, sizeof(int), 3);
    y = two_d_fetch_row(d, 12, 42, sizeof(int)) + two_d_fetch_row(d, 10, 15, sizeof(int));

    printf("y = %d\n", y);
    two_d_dealloc(d);
}
void columnMajorTest() {
    printf("Column major test\n");
    char *d;
    int y;
    d = two_d_alloc(20, 50, sizeof(int));
    two_d_store_column(d, 12, 42, sizeof(int), 4);
    two_d_store_column(d, 10, 15, sizeof(int), 3);
    y = two_d_fetch_column(d, 12, 42, sizeof(int)) + two_d_fetch_column(d, 10, 15, sizeof(int));

    printf("y = %d\n", y);
    two_d_dealloc(d);
}
int main() {
    rowMajorTest();
    columnMajorTest();

    return 0;
}
