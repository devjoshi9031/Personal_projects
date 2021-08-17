#include "cbfifo.h"
#include <stdio.h>
#include<string.h>

#define SIZE 127


char circular_buffer[SIZE];
int buffer_empty = 1, buffer_full=0;
int HEAD=0, TAIL=0;
char *test = "To be, or not to be: that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "The slings and arrows of outrageous fortune,\n"
    "Or to take arms against a sea of troubles,\n"
    "And by opposing end them? To die, to sleep--\n"
    "No more--and by a sleep to say we end\n"
    "The heart-ache and the thousand natural shocks\n"
    "That flesh is heir to, 'tis a consummation\n"
    "Devoutly to be wish'd. To die, to sleep;\n"
    "To sleep: perchance to dream: ay, there's the rub;\n"
    "For in that sleep of death what dreams may come\n"
    "When we have shuffled off this mortal coil,\n"
    "Must give us pause.";
    char buffer[1024];

size_t cbfifo_enqueue(void *buf, size_t nbyte){
   // printf("Inside Enqueue function\n");
    
    if(buffer_full==1 || nbyte==0){
   //     printf("Buffer already FULL: ABORTING!!!\n");
        return 0;
    }
    buffer_empty = 0;
    int i=0;
    for (i=0; i<nbyte; i++){
        circular_buffer[HEAD] = *(test+i);
    //    printf("%c \t %d\n",circular_buffer[HEAD], HEAD);
        HEAD = (HEAD+1)%SIZE;
        if(HEAD==TAIL){
       //     printf("Buffer FULL: ABORTING!!!");
            return i+1;
            buffer_full = 1;
        }
    }
    return i;
}

size_t cbfifo_dequeue(void *buf, size_t nbyte){
   // printf("Inside Dequeue function\n");
    
    int i=0;
    if(buffer_empty==1 || nbyte==0){
    //    printf("Buffer Already Empty: ABORTING!!");
    
        return 0;
    }
    buffer_full = 0;
        for (int i=0; i<nbyte; i++){
        (buffer[i]) = circular_buffer[TAIL];
        circular_buffer[TAIL]='\0';

      //  printf("%c \t %d\t %d\n",buffer[i], TAIL,i);
        TAIL = (TAIL+1)%SIZE;
        if(TAIL==HEAD){
       //     printf("Buffer Empty: ABORTING!!!\n");
            buffer_empty = 1;
            return i+1;
        }
        
    }
    printf("TAIL: %d\t HEAD: %d\n",TAIL,HEAD);
    return i+1;

}

size_t cbfifo_length(){
    if(HEAD<TAIL){
    //    printf("The size of the Circular buffer is: %d\n",SIZE-TAIL+HEAD);
        return 128-TAIL+HEAD;
    }
    else if(HEAD>TAIL){
     //   printf("The size of the Circular buffer is: %d\n",HEAD-TAIL);
        return HEAD-TAIL;
    }
    else{
      //  printf("The size of the Circular buffer is: %d\n",strlen(circular_buffer));
        return strlen(circular_buffer);
    }
        


}
size_t cbfifo_capacity(){
    return SIZE;
}
// void main(){
    
    

//     //Implementation for the enqueue function call;
//     cbfifo_enqueue(test,20);
//     cbfifo_length();
//     //printf("Starting the dequeue operation with tail: %d\n",TAIL%SIZE);
//     printf("strncmp: %s\n",circular_buffer[HEAD]);

//     //printf("Starting the dequeue operation with tail: %d\n",TAIL%SIZE);
//     cbfifo_dequeue(&buffer[5],20);
//     cbfifo_length();
//     printf("Buffer: %s\n",buffer);
    
//     cbfifo_enqueue(test,20);
//     cbfifo_length();
//     cbfifo_dequeue(buffer,5);
//     cbfifo_length();
//     cbfifo_dequeue(buffer,20);
//     cbfifo_length();

//     cbfifo_enqueue(test,SIZE);
//     cbfifo_length();
//     cbfifo_dequeue(buffer,SIZE);
//     cbfifo_length();

//     cbfifo_enqueue(test,20);
//     cbfifo_length();
//     cbfifo_dequeue(buffer,18);
//     cbfifo_length();



//     // cbfifo_enqueue(test,129);
//     // cbfifo_length();
//     // cbfifo_enqueue(test,1);
//     // cbfifo_dequeue(buffer,129);
//     // cbfifo_length();
//     // cbfifo_dequeue(buffer,10);
 

// }