#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>

typedef enum{
    CLEAR,
    SET,
    TOGGLE,
} operation_t;

uint32_t twiggle_bit(uint32_t input, int bit, operation_t operation){
    if(bit>31)
        goto error;
    if(operation == CLEAR){
        input = input & 0 << bit;
    }
    else if(operation == SET){
        input = input | 1 << bit;
    }
    else if (operation == TOGGLE)
    {
        /* code */
        input = input ^ 1 << bit;
    }
    else
        error: return 0xFFFFFFFF;
    
    return input;
    
}

void main(){
    operation_t operation=TOGGLE;
    int bit=0;
    uint32_t input=1;
    uint32_t answer = twiggle_bit(input, bit, operation);
    printf("%d\t %x\n",answer, answer);
}

