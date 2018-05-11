#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  struct node *link;
  int data;
}node;

node *makenode(int num){
  node* tmp = malloc(sizeof(node));
  tmp -> data = num;
  tmp -> link = NULL;
  return tmp;
}

void load(int *x,node **head,node **tail){
  int i;
  int nodeNum;
  
  for(i=0;i<5;i++){
    nodeNum+=1;
    if(*head == NULL){
      *head = *tail =  makenode(x[i]);
    }else{
      node * tmp = makenode(x[i]);
      (*tail)->link = tmp;
      *tail = tmp;
    }
  }
}
int main(){
  int x[] = {1,2,2,4,5};
  node *head = NULL,*tail = NULL,*tmp;
  load(x,&head,&tail);
  for(tmp=head;tmp!=NULL;tmp = tmp->link){
    printf("%d\n",tmp->data);
  }
}
