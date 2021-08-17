#include "cbfifo.h"
#include <stdio.h>
#include<string.h>

#define SIZE 127


char circular_buffer[SIZE];
int buffer_empty = 1, buffer_full=0;
int HEAD=0, TAIL=0;

size_t cbfifo_enqueue(void *buf, size_t nbyte){    
    if(buffer_full==1 || nbyte==0){
        return 0;
    }
    
    buffer_empty = 0;
    int j=0;
    for (int i=0; i<nbyte; i++){
        circular_buffer[HEAD] = *((char*)buf);
        HEAD = (HEAD+1)%SIZE;
        j++;
        buf++;
        if(HEAD==TAIL){
            buffer_full = 1;
            return j;
            
        }
    }
    return j;
}

size_t cbfifo_dequeue(void *buf, size_t nbyte){
    int j=0;
    if(buffer_empty==1 || nbyte==0){    
        return 0;
    }
    char temp[1024];
    buffer_full = 0;
    for(int i=0; i<nbyte; i++){
        temp[i] = circular_buffer[TAIL]; 
        strncpy((char *)buf, &circular_buffer[TAIL],1);
        circular_buffer[TAIL]='\0';
        TAIL = (TAIL+1)%SIZE;
        j=j+1;
        buf++;
        if(TAIL==HEAD){     
            buffer_empty = 1;
            return j;
        }
    }
   
    return j;
}

size_t cbfifo_length(){
    if(HEAD<TAIL){
        return 127-TAIL+HEAD;
    }
    else if(HEAD>TAIL){
        return HEAD-TAIL;
    }
    else{
        return strlen(circular_buffer);
    }
}
size_t cbfifo_capacity(){
    return SIZE;
}

//   char *str ="To be, or not to be: that is the question:\n"
//     "Whether 'tis nobler in the mind to suffer\n"
//     "The slings and arrows of outrageous fortune,\n"
//     "Or to take arms against a sea of troubles,\n"
//     "And by opposing end them? To die, to sleep--\n"
//     "No more--and by a sleep to say we end\n"
//     "The heart-ache and the thousand natural shocks\n"
//     "That flesh is heir to, 'tis a consummation\n"
//     "Devoutly to be wish'd. To die, to sleep;\n"
//     "To sleep: perchance to dream: ay, there's the rub;\n"
//     "For in that sleep of death what dreams may come\n"
//     "When we have shuffled off this mortal coil,\n"
//     "Must give us pause.";
// char buffer[1024];
// void main(){
    
//     printf("%d\n",cbfifo_enqueue(str,11));
//     printf("%d\n",cbfifo_dequeue(buffer,11));
//     printf("%d\n",strncmp(buffer,str,11));
// }