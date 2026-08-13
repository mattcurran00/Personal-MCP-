#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef int32_t i32;

typedef struct{
    i32 data;
    struct Node* next;
} Node;

typedef struct{
    Node* head;
}list;

Node* createNode(i32 data);

int main (){ 

    i32 v;
    printf("\n------ Some Linked List Nonsense ------\n Give us a value: ");
    scanf("%d", &v);

    Node* new = createNode(v);

    return 0;
}

Node* createNode( i32 data){

    Node* nstNode = (Node*)malloc(sizeof(Node));
    nstNode->data = data;
    nstNode->next = NULL; //bc its the most recent one 
    return nstNode;
}
