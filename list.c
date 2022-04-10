#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct t_node {
    int value;
    char fixed;
    struct t_node *next;
} typedef Node;

Node *newNode(int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->value = value;
    node->fixed = 21;
    node->next = NULL;
    return node;
}

void addNode(Node *list, int value) {
    Node *node = newNode(value);
    Node *tmp = list;
    for (; tmp; tmp = tmp->next) {
        if (tmp->next == NULL) {
            tmp->next = node;
            return;
        }
    }
}

void listOf10(Node *list) {
    for (int i = 1; i < 10; ++i) {
        addNode(list, i);
    }
}

void printList(Node *list) {
    for (Node *tmp = list; tmp; tmp = tmp->next) {
        printf("Size of %p is %d, next: %p, value: %d, fixed: %d\n", tmp, sizeof(*tmp), tmp->next, tmp->value,
               tmp->fixed);
    }
}

void freeList(Node *list) {
    Node *tmp = list;
    Node *toDel = list;
    for (; tmp;) {
        toDel = tmp;
        tmp = tmp->next;
        free(toDel);
    }
}

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

void storeInt(char *d, int index, int value) {
    int shift;
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        d[index + i] = (char) ((value >> shift) & 0xFF);
    }
}

void storeNode(char *d, int index, Node *value) {
    int shift;
    for (int i = 0; i < sizeof(Node *); ++i) {
        shift = i * 8;
        d[index + i] = (char) (((intptr_t) value->next >> shift) & 0xFF);
    }
    index += sizeof(Node *);
    shift = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        d[index + i] = (char) ((value->value >> shift) & 0xFF);
    }
    index += sizeof(int);
    d[index] = value->fixed;
}

int getInt(const char *d, int index) {
    int shift;
    int value = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        value = value | (((int) (d[index + i]) << shift) & (0xFF << shift));
    }
    return value;
}

Node getNode(const char *d, int index) {
    Node node;
    int shift;
    intptr_t intptr = 0;
    for (int i = 0; i < sizeof(Node *); ++i) {
        shift = i * 8;
        intptr = intptr | (((int) (d[index + i]) << shift) & (0xFF << shift));
    }
    node.next = (Node *) intptr;
    index += sizeof(Node *);

    int tmpInt = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        shift = i * 8;
        tmpInt = tmpInt | (((int) (d[index + i]) << shift) & (0xFF << shift));
    }
    node.value = tmpInt;
    index += sizeof(int);

    node.fixed = d[index];
    return node;
}

struct vec_2 {
    int x, y;
} typedef Vec2;

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

void memoryDump(char *d, int size) {
    Vec2 dim = getDimensions(d);
    int length = (dim.x * dim.y);
    for (int i = 0; i < length; i++) {
        int pos = i * size + 2 * (int) sizeof(int);
        printf("\n%p ", &(d[pos]));
        for (int j = 0; j < size; j++) {
            printf("%02x ", d[pos + j]);
        }
        for (int j = 0; j < size; j++) {
            if (d[pos + j] == 0)
                printf(". ");
            else
                printf("%c ", d[pos + j]);
        }
    }
    printf("\n");
}

char *two_d_alloc(int x, int y, int size) {
    int length = size * x * y + (int) sizeof(int) * 2;
    char *d = (char *) malloc(length);
    for (int i = 0; i < length; i++)
        d[i] = 0;

    storeInt(d, 0, x);
    storeInt(d, 4, y);
    return d;
}

void two_d_dealloc(char *d) {
    free(d);
}

void two_d_store_row(char *d, int x, int y, int size, int value) {
    Vec2 dim = getDimensions(d);
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    storeInt(d, index, value);
}

void two_d_store_row_node(char *d, int x, int y, int size, Node *value) {
    Vec2 dim = getDimensions(d);
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    storeNode(d, index, value);
}

int two_d_fetch_row(char *d, int x, int y, int size) {
    Vec2 dim = getDimensions(d);
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    return getInt(d, index);
}

Node two_d_fetch_row_node(char *d, int x, int y, int size) {
    Vec2 dim = getDimensions(d);
    int index = (x + y * dim.x) * size + 2 * (int) sizeof(int);
    return getNode(d, index);
}

void two_d_store_column(char *d, int x, int y, int size, int value) {
    Vec2 dim = getDimensions(d);
    int index = (x * dim.y + y) * size + 2 * (int) sizeof(int);
    storeInt(d, index, value);
}

int two_d_fetch_column(char *d, int x, int y, int size) {
    Vec2 dim = getDimensions(d);
    int index = (x * dim.y + y) * size + 2 * (int) sizeof(int);
    return getInt(d, index);
}

int main() {


    Node *list = newNode(0);
    listOf10(list);
    printf("asd\n");
    printList(list);
    //printf("\nSize of %p is %d value: %d, fixed: %d\nSize of value: %d, fixed: %d, next: %d\n",
    //       list, sizeof(*list), list->value, list->fixed, sizeof(list->value), sizeof(list->fixed), sizeof(list->next));

    char *d;
    int y;
    d = two_d_alloc(10, 1, sizeof(Node));

    printf("Node size: %d, dimensions: %d - %d\n", sizeof(Node), getDimensions(d).x, getDimensions(d).y);
    //two_d_store_row_node(d, 0, 0, sizeof (Node), &(list[1]));
    int i = 0;
    for (Node *tmp = list; tmp; tmp = tmp->next) {
        //printf("Size of %p is %d value: %d, fixed: %d\n", tmp, sizeof(*tmp), tmp->value, tmp->fixed);
        two_d_store_row_node(d, i, 0, sizeof(Node), tmp);
        i++;
    }
    y = two_d_fetch_row_node(d, 5, 0, sizeof(Node)).value + two_d_fetch_row_node(d, 8, 0, sizeof(Node)).value;
    memoryDump(d, sizeof(Node));
    printf("Node size: %d, dimensions: %d - %d\n", sizeof(Node), getDimensions(d).x, getDimensions(d).y);
    //visualizeData(d, sizeof(Node));
    //two_d_fetch_row_node()

    for (i = 0; i < 10; i++) {
        Node tmp = two_d_fetch_row_node(d, i, 0, sizeof(Node));
        printf("Index: %d, Next: %p, Value: %d, Static: %d\n", i, tmp.next, tmp.value, tmp.fixed);
    }

    printf("y = %d\n", y);
    two_d_dealloc(d);

    freeList(list);
    printf("dsa\n");
    return 0;
}
