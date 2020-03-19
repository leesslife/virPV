#include "ListVirPV.h"

virPvList *create(int n,void *stru){
    virPvList *head,*node,*end;
    head=(virPvList*)malloc(sizeof(virPvList));
    end=head;
    for(int i=0;i<n;i++){
        node=(virPvList*)malloc(sizeof(virPvList));
        //scanf("%d",&node->score);
        node->inpstruct=stru;
        end->next=node;
        end=node;
    }
    end->next;
    return head;
}

void change(virPvList *list,int n,void *stru){
    virPvList *t=list;
    int i=0;
    while(i<n&&t!=NULL){
        t=t->next;
        i++;
    }
    if(t!=NULL){
        //puts("intput val");
        //scanf("%d",&t->score);
        t->inpstruct=stru;
    }
    else{
        //puts("node is not exsit");
    }
}

void delet(virPvList *list,int n)
{
    virPvList *t=list,*in;
    int i=0;
    while (i<n&&t!=NULL){
        in=t;
        t=t->next;
        i++;
    }
    if(t!=NULL){
        in->next=t->next;
        free(t->inpstruct);
        free(t);
    }
    else{
        puts("no node");
    }
}

void insert(virPvList *list,int n,void *stru){
    virPvList *t=list,*in;
    int i=0;
    while(i<n &&t!=NULL){
        t=t->next;
        i++;
    }
    if(t!=NULL){
        in=(virPvList*)malloc(sizeof(virPvList));
        in->inpstruct=stru;
        //puts("insert your value");
        //scanf("%d",&in->score);
        in->next=t->next;
        t->next=in;
    }
    else{
        //puts("no node");
    }
}
void insert_tail(virPvList *list,void *stru){
    virPvList *t=list,*in;
    int i=0;
    while(t->next!=NULL){
        t=t->next;
        i++;
    } 
    in=(virPvList*)malloc(sizeof(virPvList));
    in->inpstruct=stru;
    in->next=NULL;
    t->next=in;
}

/*void printList(){
    virPvList *h;
    while(h->next!=NULL){
        h=h->next;
        printf("%d",h->score);
    }
}*/
