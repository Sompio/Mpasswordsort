//#include <stdio.h>
//#include "list.h"

/*list* list_create(void) {
    list *l = malloc(sizeof(list));
    l->head = malloc(sizeof(node));
    l->head->next = l->head;
    l->head->previous = l->head;

    return l;
}

data* list_inspect(list *l, list_position p) {
    return p->value;
}

list_position list_insert(list *l, list_position p, data d) {
    list_position newNode = malloc(sizeof(node));
    newNode->value = d;
    newNode->next = p;
    newNode->previous = p->previous;

    p->previous = newNode;
    newNode->previous->next = newNode;
    return newNode;
}

list_position list_length(list *l);

//void list_setMemHandler(list *l, memFreefunc *f);

bool list_isEmpty(list *l) {
    return (l->head->next == l->head);
}

list_position list_first(list *l) {
    return l->head->next;
}

list_position list_end(list *l) {
    return l->head->previous;
}

list_position list_next(list *l, list_position p) {
    return p->next;
}

list_position list_previous(list *l, list_position p) {
    return p->previous;
}

list_position list_remove(list *l, list_position p) {
    list_position retur = p->next;
    p->previous->next = p->next;
    p->next->previous = p->previous;

    if(l->freeFunc != NULL)
        l->freeFunc(p->value);
    free(p);
    return retur;
}

void list_free(list *l);
*/

#include "list.h"


//create empty list, constructor
list *listEmpty(void) {
    list *newList=malloc(sizeof(struct list));
    if(newList == NULL) {
        perror("list memory allocation\n");
        exit(EXIT_FAILURE);
    }
    newList->head=malloc(sizeof(element));
    if(newList->head == NULL) {
        perror("list head memory allocation\n");
        exit(EXIT_FAILURE);
    }
    newList->head->next=newList->head;
    newList->head->previous=newList->head;
    newList->freeFunc=NULL;
    return newList;
}


// set mem handler
void listSetMemHandler(list *l, memFreeFunc *f){
    l->freeFunc=f;
}


// return first position
listPosition listFirst(list *l){
    return l->head->next;
}

// return last position
listPosition listLast(list *l){
    return l->head->previous;
}

// get next position
listPosition listNext(listPosition p) {
    return p->next;
};

// get previous position
listPosition listPrevious(listPosition p){
    return p->previous;
};

// is list empty
bool listIsEmpty(list *l) {
    return (l->head->next == l->head);
}

// insert list element
listPosition listInsert(listPosition p,data d) {
    listPosition newPosition=malloc(sizeof(element));
    if(newPosition == NULL){
        perror("Memory allocation for new list element\n");
        exit(EXIT_FAILURE);
    }
    newPosition->data=d;
    newPosition->next=p->next;
    (p->next)->previous=newPosition;
    newPosition->previous=p;
    p->next=newPosition;
    return newPosition;

};

// inspect list element
data* listInspect(listPosition p) {
    return p->data;
};

// remove list element
listPosition listRemove(list *l, listPosition p) {
    listPosition beforeRemove=p->previous;
    p->previous->next=p->next;
    p->next->previous=p->previous;
    if(l->freeFunc!=NULL)
        l->freeFunc(p->data);
    free(p);
    return beforeRemove;
};

// free memory
void listFree(list *l){
    listPosition current = listLast(l);
    while (listIsEmpty(l) != true) {
        current = listRemove(l, current);
    }
    free(l->head);
    free(l);
};



// check if end of list
bool listIsEnd(list *l, listPosition p){
    if ( p->next == l->head) {
        return true;
    } else {
        return false;
    }
};