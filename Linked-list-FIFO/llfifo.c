#include "llfifo.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#define SIZE 128

struct llfifo_s{
    char msg[SIZE];
    int tag;
    struct llfifo_s* link;
};

//llfifo_t *head;

llfifo_t *llfifo_create(int capacity){
    llfifo_t *node, *tmp,*head=NULL;
    if(capacity==0)
        return NULL;                 // This is to get two extra nodes. 1 for mallocing and 1 for traversing.
    for(int i=1;i<=capacity;i++){
        tmp = (llfifo_t *) malloc(sizeof(llfifo_t));        //malloc untill the capacity of nodes reached.

        if(tmp==NULL){
            perror("Problem with Malloc");
            exit(1);
        }
        tmp->msg[0] = '\0';
        tmp->tag = i;
        tmp->link = NULL;
        if(i==1){
            head=tmp;
            //("In create: %s and strlen: %d\n",head->msg,strlen(head->msg));
            continue;

        }
        node=head;
        while(node->link!=NULL){
                node = node->link;
            }
            node->link = tmp;
    }// end of for
    return head;
}// end of llfifo_create

int llfifo_length(llfifo_t *fifo){
    int length =0;
    llfifo_t *tmp;
    tmp = fifo;
    if(fifo->link == NULL && strlen(fifo->msg)==0){
        return length;
    }
    while(tmp->link!=NULL){
        if(strlen(tmp->msg) == 0){
            // //(" In Length: %d\n",tmp->tag);
            tmp = tmp->link;
            continue;
        }
        // //("In Length: %d\n",tmp->tag);
        tmp = tmp->link;
        length++;
    }
    if((tmp->link == NULL && (strlen(tmp->msg) == 0)))        
        return length;
    else
        return length+1;
}


int llfifo_capacity(llfifo_t *fifo){
    int capacity =1;
    llfifo_t *tmp;
    tmp = fifo;
    while(tmp->link!=NULL){            
        tmp = tmp->link;
        capacity++;
    }
        
    return capacity;
}

void llfifo_destroy(llfifo_t *fifo){
    llfifo_t *tmp;
    while(fifo->link!=NULL){
        tmp = fifo;        
        fifo = fifo->link;
        if(fifo->link==NULL){
            free(tmp);
           // //("In destroy in if: %d\n",tmp->tag);
            free(fifo);
           // //("In destroy in if: %d\n",fifo->tag);
            return;
        }
       // //("In destroy: %d\n",tmp->tag);
        free(tmp);
    }
    return;
}

int llfifo_enqueue(llfifo_t *fifo, void *element){
    llfifo_t *tmp;
    int length=0;
    //printf("Tag\tString\n");
    //First node and if it is empty! THis works great.
    if((strlen(fifo->msg)==0)){
        strcpy(fifo->msg,(char*)element);
        //("%d\t%s\t\n",fifo->tag,fifo->msg);
        length++;
        return length;
    }
    //For all the other nodes that are between head and last element!
    while(fifo->link!=NULL){
        if(strlen(fifo->msg) == 0){
            // fifo->msg = *(char*)element;
            strcpy(fifo->msg,(char*)element);
            //("%d\t%s\t\n",fifo->tag,fifo->msg);
            length++;
            return length;
        }
        length++;
        fifo = fifo->link;
    }
    //This is for the last element if added and the msg is nothing;
    if(strlen(fifo->msg) == 0){
            strcpy(fifo->msg,(char*)element);
            //("%d\t%s\t\n",fifo->tag,fifo->msg);
            length++;
            return length;
    }
    //Finally if length == CApapcity and a new node has to be added!
    else{
        tmp = (llfifo_t*)malloc(sizeof(llfifo_t));
        strcpy(tmp->msg,(char*)element);
        //("%d\t%s\t\n",fifo->tag,fifo->msg);
        tmp->link = NULL;
        fifo->link = tmp;
        length++;
        return length;
    }
    return length;

}

void *llfifo_dequeue(llfifo_t *fifo){
    llfifo_t *tmp;
    char ans[128];
    if(strlen(fifo->msg)==0)
        return NULL;
    tmp = fifo;
    fifo = fifo->link;    
    strcpy(&ans[0],tmp->msg);
  //  printf("Return: %s\n",ans);
    return (void*)ans;
    
}
// void main(){
//         llfifo_t *head;
//           char *strs[] =
//     { "To be, or not to be: that is the question:",
//       "Whether 'tis nobler in the mind to suffer",
//       "The slings and arrows of outrageous fortune,",
//       "Or to take arms against a sea of troubles,",
//       "And by opposing end them? To die, to sleep—",
//       "No more—and by a sleep to say we end",
//       "The heart-ache and the thousand natural shocks",
//       "That flesh is heir to, 'tis a consummation",
//       "Devoutly to be wish'd. To die, to sleep;",
//       "To sleep: perchance to dream: ay, there's the rub;",
//       "For in that sleep of death what dreams may come",
//       "When we have shuffled off this mortal coil,",
//       "Must give us pause."
//     };
//         head=llfifo_create(4);
//         //("capacity: %d\n",llfifo_capacity(head));    
//         //("Length: %d\n",llfifo_length(head));
    
//         llfifo_enqueue(head,strs[0]);
//         //("capacity: %d\n",llfifo_capacity(head));    
//         //("Length: %d\n",llfifo_length(head));
    
//         llfifo_enqueue(head,strs[1]);
//         //("capacity: %d\n",llfifo_capacity(head));    
//         //("Length: %d\n",llfifo_length(head));
//         llfifo_enqueue(head,strs[2]);
//         //("capacity: %d\n",llfifo_capacity(head));    
//         //("Length: %d\n",llfifo_length(head));
//         llfifo_destroy(head);
        
        

// }