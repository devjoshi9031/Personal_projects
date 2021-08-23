#include "llfifo.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#define SIZE 128
char ans[SIZE];     // array to send the dequeued element from the LLFIFO.
struct llfifo_s{
    char msg[SIZE];
    int tag;
    struct llfifo_s* link;
};

llfifo_t *llfifo_create(int capacity){
    llfifo_t *node, *tmp,*start=NULL;
    // This to check if the capacity is a valid number.
    if(capacity==0)             
        return NULL;              

    for(int i=0;i<capacity;i++){
        tmp = (llfifo_t *) malloc(sizeof(llfifo_t));        //malloc untill the capacity of nodes reached.

        if(tmp==NULL){
            perror("Problem with Malloc");
            exit(1);
        }
        tmp->msg[0] = '\0';
        tmp->tag = i;
        tmp->link = NULL;
        // variable to return the head of the LLFIFO.
        if(i==0){
            start=tmp;
            continue;
        }
        // Traverse the linked list and attach a new element at the end of the FIFO.
        node=start;
        while(node->link!=NULL){
                node = node->link;
            }
            node->link = tmp;
    }// end of for
    return start;
}// end of llfifo_create


int llfifo_enqueue(llfifo_t *fifo, void *element){
    llfifo_t *tmp;
    int length=0,copy=0,return_length = 0,non_empty=0;
    length = llfifo_length(fifo);               // Get the current length of the FIFO.
    int capacity = llfifo_capacity(fifo);       // Get the current capacity of the FIFO.
    tmp=fifo;
    // Traverse the whole FIFO and check if any element has the tmp->msg field empty. If so insert the element at that node.
    while(tmp!=NULL){
        if(strlen(tmp->msg)!=0){
            non_empty=1;
            break;
        }
        tmp=tmp->link;
    }
    // If the linked list is empty start inserting at the first node!
    if(non_empty==0)
        tmp = fifo;
    for(int i=1;i<=capacity;i++){
        if((strlen(tmp->msg)==0) && (copy==0)){
            copy=1;
            strcpy(tmp->msg,(char*)element);
            length++;
        }
        if(tmp->link == NULL)
            break;
        tmp=tmp->link;        
    }
    //check for the last element. If it is the only element empty then write in that element!
    if((strlen(tmp->msg)==0) && (copy==0)){
        copy=1;
        strcpy(tmp->msg,(char*)element);
        length++;
    }
    // If capacity is reached, then add another node!

    if(copy==0){
        llfifo_t *new_node;
            new_node = (llfifo_t*)malloc(sizeof(llfifo_t));
            strcpy(new_node->msg,(char*)element);
            new_node->link = NULL;
            tmp->link = new_node;
            length++;
    }
return length;    
}


int llfifo_dequeue(llfifo_t *fifo){
    memset(&ans[0],'\0',SIZE);          //empty the character array.
    int capacity;
    capacity = llfifo_capacity(fifo);   //Get the capacity of the FIFO
    if(capacity==0)
        return NULL;
    llfifo_t *tmp;
    //start from the first element and traverse the whole FIFO to get any element that is not being dequeued.
    tmp=fifo;
    for(int i=0; i<capacity;i++){
        if(strlen(tmp->msg)!=0){
            strcpy(&ans[0],tmp->msg);
            memset(tmp->msg,'\0',SIZE);
            tmp->msg[0]='\0';
            return strlen(ans);
        } 
         if(tmp->link == NULL){
             break;
         }
        tmp=tmp->link;        
    }
    // Check for the last element if it has any msg to deqeueue.
    if((strlen(tmp->msg))!=0){
            strcpy(&ans[0],tmp->msg);
            memset(tmp->msg,'\0',SIZE);
            tmp->msg[0]='\0';
            return strlen(ans);
    }
    return NULL;
}

//PRINT function to print the whole LLFIFO.
void print(llfifo_t *fifo){
    llfifo_t *start;
    start = fifo;
    printf("PRINT FUNCTION:\n");
    while(start!=NULL){
        if(strlen(start->msg)==0){
            start=start->link;
            continue;
        }            
        printf("%s\n",start->msg);
        start=start->link;
    }
}

void llfifo_destroy(llfifo_t *fifo){
    llfifo_t *tmp;
    while(fifo->link!=NULL){
        tmp = fifo;        
        fifo = fifo->link;
        if(fifo->link==NULL){
            free(tmp);
            free(fifo);
            return;
        }
        free(tmp);
    }
    return;
}


int llfifo_length(llfifo_t *fifo){
    int length =0;
    llfifo_t *tmp;
    tmp = fifo;
    if(fifo==NULL)
        return length;
    if(fifo->link == NULL && strlen(fifo->msg)!=0){
        return ++length;
    }
    while(tmp->link!=NULL){
        if(strlen(tmp->msg) == 0){
            tmp = tmp->link;
            continue;
        }
        tmp = tmp->link;
        length++;
    }
    if((tmp->link == NULL && (strlen(tmp->msg) != 0)))        
        return ++length;
    return length;
}


int llfifo_capacity(llfifo_t *fifo){
    int capacity =1;
    llfifo_t *tmp;
    tmp = fifo;
    if(tmp==NULL)
        return 0;
    while(tmp->link!=NULL){    
        tmp = tmp->link;
        capacity++;
    }        
    return capacity;
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