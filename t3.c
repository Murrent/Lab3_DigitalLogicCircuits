#include <stdio.h>
#include "list.h"

int main() {
    // Creating the first node
    Node *list = newNode(0);
    // Adding 9 more nodes making it a linked list of 10 nodes
    // The values of the nodes will range from 0-9 and the fixed value will be 21
    listOf10(list);
    // Printing the size of the struct and the size of the fields
    printf("Size of struct: %llu, size of fields: %llu\n", sizeof(Node),
           sizeof(list->next) + sizeof(list->value) + sizeof(list->fixed));
    // Printing all information about the list
    printf("\nLinked list content:\n");
    printList(list);

    char *d;
    // Allocating a char array to store 10 * 1 nodes
    d = two_d_alloc(10, 1, sizeof(Node));

    // Storing the linked list in the char array
    int i = 0;
    for (Node *tmp = list; tmp; tmp = tmp->next) {
        two_d_store_row_node(d, i, 0, sizeof(Node), tmp);
        i++;
    }

    printf("\nChar array memory dump:");
    memoryDump(d, sizeof(Node));
    printf("\n");


    printf("\nChar array fetch test for all elements:\n");
    for (i = 0; i < 10; i++) {
        Node tmp = two_d_fetch_row_node(d, i, 0, sizeof(Node));
        printf("Index: %d, Next: %p, Value: %d, Static: %d\n", i, tmp.next, tmp.value, tmp.fixed);
    }

    printf("\nFetching in row major mode, locations x: 5, y: 0, and x: 8, y: 0, then then add them together:\n");
    int y;
    y = two_d_fetch_row_node(d, 5, 0, sizeof(Node)).value + two_d_fetch_row_node(d, 8, 0, sizeof(Node)).value;
    printf("y = %d\n", y);

    two_d_dealloc(d);
    freeList(list);
    return 0;
}