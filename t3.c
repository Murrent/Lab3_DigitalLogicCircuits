#include <stdio.h>
#include "list.h"

int main() {
    Node *list = newNode(0);
    listOf10(list);
    printf("Size of struct: %d, size of fields: %d\n", sizeof(Node),
           sizeof(list->next) + sizeof(list->value) + sizeof(list->fixed));
    printList(list);

    char *d;
    d = two_d_alloc(10, 1, sizeof(Node));

    int i = 0;
    for (Node *tmp = list; tmp; tmp = tmp->next) {
        two_d_store_row_node(d, i, 0, sizeof(Node), tmp);
        i++;
    }

    memoryDump(d, sizeof(Node));
    printf("\n");

    for (i = 0; i < 10; i++) {
        Node tmp = two_d_fetch_row_node(d, i, 0, sizeof(Node));
        printf("Index: %d, Next: %p, Value: %d, Static: %d\n", i, tmp.next, tmp.value, tmp.fixed);
    }

    int y;
    y = two_d_fetch_row_node(d, 5, 0, sizeof(Node)).value + two_d_fetch_row_node(d, 8, 0, sizeof(Node)).value;
    printf("y = %d\n", y);

    two_d_dealloc(d);
    freeList(list);
    return 0;
}