#ifndef LISTVIRPV_H
#define LISTVIRPV_H
#include <stdio.h>
#include <stdlib.h>
typedef struct student{
    void *inpstruct;
    //int score;
    struct student *next;
}virPvList;

virPvList *create(int n,void *stru);
void change(virPvList *list,int n,void *stru);
void delet(virPvList *list,int n);
void insert(virPvList *list,int n,void *stru);
void insert_tail(virPvList *list,void *stru);
//oid printList();
#endif

