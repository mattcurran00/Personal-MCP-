#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t ui8;
typedef uint16_t ui16;
typedef uint32_t u32;

typedef struct{
    i32 data;
    struct vect* vect; //pointer to the nodes vector?
    struct Node* next;
} Node;

/**
 * what is this to be?
 * a set of coordinates, origin and destination and the weighting
 */
typedef struct{
    i32 x;
    i32 y;
    i32 z;
    struct Node* orig;
    struct Node* dest;
}vect;

/**
 * struct of co-ordinates for any given point
 */
typedef struct{
    i32 x;
    i32 y;
}cd;

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
