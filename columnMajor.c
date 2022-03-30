#include <stdio.h>
#include <stdlib.h>

void printInt(int value) {
    int size = sizeof(int) * 8;
    for (int i = 0; i < size; ++i) {
        if ((value >> (size - i - 1)) & 0b1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void storeInt(char *d, int index, int size, int value) {
    index = index * size;
    int shift;
    for (int i = 0; i < size; ++i) {
        shift = i * 8;
        d[index + i] = (char) ((value >> shift) & 0xFF);
    }
}

int getInt(const char *d, int index, int size) {
    index = index * size;
    int shift;
    int value = 0;
    for (int i = 0; i < size; ++i) {
        shift = i * 8;
        value = value | (((int) (d[index + i]) << shift) & (0xFF << shift));
    }
    return value;
}

struct vec_2 {
    int x, y;
} typedef Vec2;

Vec2 getDimensions(char *d) {
    Vec2 vec2;
    vec2.x = getInt(d, 0, sizeof(int));
    vec2.y = getInt(d, 1, sizeof(int));
    return vec2;
}

void visualizeData(char *d, int size) {
    Vec2 dim = getDimensions(d);
    int length = (dim.x * dim.y + 2) * size;
    for (int i = 0; i < length; i++) {
        if (i % (dim.x * size) - 8 == 0)
            printf("\n");
        if (d[i] == 0)
            printf(".");
        else
            printf("%x", d[i]);
    }
    printf("\n");
}

char *two_d_alloc(int x, int y, int size) {
    int length = size * x * y + (int)sizeof(int) * 2;
    char *d = (char *) malloc(length);
    for (int i = 0; i < length; i++)
        d[i] = 0;

    storeInt(d, 0, sizeof(int), x);
    storeInt(d, 1, sizeof(int), y);
    return d;
}

void two_d_dealloc(char *d) {
    free(d);
}

void two_d_store_column(char *d, int x, int y, int size, int value) {
    Vec2 dim = getDimensions(d);
    int index = (x * dim.y + y) + 2;
    storeInt(d, index, size, value);
}

int two_d_fetch_column(char *d, int x, int y, int size) {
    Vec2 dim = getDimensions(d);
    int index = (x * dim.y + y) + 2;
    return getInt(d, index, size);
}

int main() {
    char *d;
    int y;
    d = two_d_alloc(20, 50, sizeof(int));
    two_d_store_column(d, 12, 42, sizeof(int), 4);
    two_d_store_column(d, 10, 15, sizeof(int), 3);
    y = two_d_fetch_column(d, 12, 42, sizeof(int)) + two_d_fetch_column(d, 10, 15, sizeof(int));
    visualizeData(d, sizeof(int));

    printf("y = %d\n", y);
    two_d_dealloc(d);
    return 0;
}
