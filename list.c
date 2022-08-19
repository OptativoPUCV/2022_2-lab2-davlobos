#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* list=(List*)malloc(sizeof(List));
  list->head=NULL;
  list->tail=NULL;
  list->current=NULL;
  
  return list;
}

void * firstList(List * list) {
  if (list->head == NULL) return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if(list->current == NULL)return NULL;
  if(list->current->next == NULL)return NULL;
  list->current =list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list->tail == NULL) return NULL;
  list->current=list->tail;
  return list->current->data;
}

void * prevList(List * list) {

  if(list->current==NULL)return NULL;
  if(list->current->prev==NULL)return NULL;
  list->current=list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *newnode = createNode(data);
  
  if (list->head != NULL){
    list->head->prev = newnode;
    newnode->next = list->head;
    list->head = newnode;
  }else{
    list->head = newnode;
    list->tail = newnode;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node *current=list->current;
  if (current == NULL)return NULL;
  if(current->prev!= NULL){
    current->prev->next = current->next;
    current->next->prev = current->prev;
  }else{
    list->head = current->next;
    list->head->prev=NULL;
  }
 // if (list->head == current){
 //   current->next->prev = NULL;
 //   list->head = current->next;
 // }else{
 //   current->prev->next = current->next;
 //   current->next->prev = current->prev;
 // }
  if(list->tail==current){
    current->prev->next=NULL;
    list->tail= current->prev;
    list->tail->next=NULL;
  }

  return current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}