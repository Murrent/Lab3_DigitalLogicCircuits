#ifndef LAB3_CA_LIST_H
#define LAB3_CA_LIST_H

#include <stdlib.h>

struct t_node {
    int value;
    char fixed;
    struct t_node *next;
} typedef Node;

// Creating a new node on the heap
Node *newNode(int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->fixed = 21;
    node->next = NULL;
    return node;
}

// Creates a node with "value" and adds it to the end of "list"
void addNode(Node *list, int value) {
    Node *node = newNode(value);
    Node *tmp = list;
    // Finds the last element and changing its "next" pointer to the new node's address
    for (; tmp; tmp = tmp->next) {
        if (tmp->next == NULL) {
            tmp->next = node;
            return;
        }
    }
}

// Shortcut for creating 9 nodes with values 1-9 and adding them to the list
void listOf10(Node *list) {
    for (int i = 1; i < 10; ++i) {
        addNode(list, i);
    }
}

// Prints information about all elements in a list
void printList(Node *list) {
    for (Node *tmp = list; tmp; tmp = tmp->next) {
        printf("Size of %p is %d, next: %p, value: %d, fixed: %d\n", tmp, sizeof(*tmp), tmp->next, tmp->value,
               tmp->fixed);
    }
}

// Free's the list
void freeList(Node *list) {
    Node *tmp = list;
    Node *toDel;
    for (; tmp;) {
        toDel = tmp;
        tmp = tmp->next;
        free(toDel);
    }
}

// Prints and integer in bits
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

// Stores an integer in the char array and the given index
void storeInt(char *d, int index, int value) {
    int shift;
    // Copies one byte from "value" each loop into the array
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        d[index + i] = (char) ((value >> shift) & 0xFF);
    }
}

// Stores a Node in the char array at the given index
void storeNode(char *d, int index, Node *value) {
    int shift;
    // Storing one byte per loop cycle to store the pointer
    for (int i = 0; i < sizeof(Node *); ++i) {
        shift = i * 8;
        d[index + i] = (char) (((intptr_t) value->next >> shift) & 0xFF);
    }
    index += sizeof(Node *); // Updating the new index we want to store at
    // Storing one byte per loop cycle to store the integer "value"
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        d[index + i] = (char) ((value->value >> shift) & 0xFF);
    }
    index += sizeof(int); // Updating the index again
    d[index] = value->fixed; // Storing the "fixed" char
}

// Returns the integer value in the char array at the given index
int getInt(const char *d, int index) {
    int shift;
    int value = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        // Copying a byte of data to the integer from the array
        value = value | (((int) (d[index + i]) << shift) & (0xFF << shift));
    }
    return value;
}

// Returns a copy of the node at the given index of the array
Node getNode(const char *d, int index) {
    Node node;
    int shift;
    intptr_t intptr = 0;
    // Copying the pointer from the array
    for (int i = 0; i < sizeof(Node *); ++i) {
        shift = i * 8;
        // Copying a byte of data to the pointer from the array
        intptr = intptr | (((int) (d[index + i]) << shift) & (0xFF << shift));
    }
    node.next = (Node *) intptr;
    index += sizeof(Node *);

    int tmpInt = 0;
    // Copying the integer from the array
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        // Copying a byte of data to the integer from the array
        tmpInt = tmpInt | (((int) (d[index + i]) << shift) & (0xFF << shift));
    }
    node.value = tmpInt;
    index += sizeof(int);

    // Copying the char from the array
    node.fixed = d[index];
    return node;
}

struct vec_2 {
    int x, y;
} typedef Vec2;

// Returns the dimensions of the array
Vec2 getDimensions(char *d) {
    Vec2 vec2;
    vec2.x = getInt(d, 0);
    vec2.y = getInt(d, 4);
    return vec2;
}

void visualizeData(char *d, int size) {
    Vec2 dim = getDimensions(d);
    int length = (dim.x * dim.y * size) + 2 * (int) sizeof(int);
    printf("Length: %d\n", length);
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

// Prints the address of the
void memoryDump(char *d, int size) {
    Vec2 dim = getDimensions(d);
    int length = (dim.x * dim.y);
    for (int i = 0; i < length; i++) {
        // Position of the beginning of the content,
        // offset by "2 * (int) sizeof(int)" to skip
        // past the array dimensions information
        int pos = i * size + 2 * (int) sizeof(int);
        // Prints the address
        printf("\n%p ", &(d[pos]));
        // Printing the hex values of the content data
        for (int j = 0; j < size; j++) {
            printf("%02x ", (unsigned char)d[pos + j]);
        }
        // Printing the ascii character of the content data
        // And prints a "." if the value is "0"
        for (int j = 0; j < size; j++) {
            if (d[pos + j] == 0)
                printf(". ");
            else
                printf("%c ", d[pos + j]);
        }
    }
    printf("\n");
}

// Allocates a char array in the size of "size" and with the dimensions of x and y
char *two_d_alloc(int x, int y, int size) {
    // The length of bytes in the array, (content + array dimension data)
    int length = size * x * y + (int) sizeof(int) * 2;
    char *d = (char *) malloc(length);
    // Setting all values to 0
    for (int i = 0; i < length; i++)
        d[i] = 0;

    // Storing the array dimension information in the beginning of the array
    storeInt(d, 0, x);
    storeInt(d, 4, y);
    return d;
}

// Freeing a char array
void two_d_dealloc(char *d) {
    free(d);
}

// Storing an integer in a char array in row major at the location x and y
void two_d_store_row(char *d, int x, int y, int size, int value) {
    Vec2 dim = getDimensions(d);
    // Calculating the single dimensional array index in row major
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    storeInt(d, index, value);
}

// Storing a Node in a char array in row major at the location x and y
void two_d_store_row_node(char *d, int x, int y, int size, Node *value) {
    Vec2 dim = getDimensions(d);
    // Calculating the single dimensional array index in row major
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    storeNode(d, index, value);
}

// Fetching an integer from a char array in row major at the location x and y
int two_d_fetch_row(char *d, int x, int y, int size) {
    Vec2 dim = getDimensions(d);
    // Calculating the single dimensional array index in row major
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    return getInt(d, index);
}

// Fetching a Node from a char array in row major at the location x and y
Node two_d_fetch_row_node(char *d, int x, int y, int size) {
    Vec2 dim = getDimensions(d);
    // Calculating the single dimensional array index in row major
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    return getNode(d, index);
}

// Storing an integer in a char array in column major at the location x and y
void two_d_store_column(char *d, int x, int y, int size, int value) {
    Vec2 dim = getDimensions(d);
    // Calculating the single dimensional array index in column major
    int index = (x * dim.y + y) * size + 2 * (int) sizeof(int);
    storeInt(d, index, value);
}

// Fetching an integer from a char array in column major at the location x and y
int two_d_fetch_column(char *d, int x, int y, int size) {
    Vec2 dim = getDimensions(d);
    // Calculating the single dimensional array index in column major
    int index = (x * dim.y + y) * size + 2 * (int) sizeof(int);
    return getInt(d, index);
}

#endif //LAB3_CA_LIST_H
