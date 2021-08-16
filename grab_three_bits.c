#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>


uint32_t grab_three_bits(uint32_t input, int start_bit){
    uint32_t op=0;  // extra variable to create a mask 

    
    // Condition to check if the start_bit does not exceed 31 mark.
    if(start_bit >= 30)
        return 0xFFFFFFFF;


    // For loop set the mask variable with appropriate start_bit.
    for(int i=0; i<3; i++){
        op = op | 1<<(start_bit+i);         // This will place 1 to 3 consecutive bits starting from start_bit.
    }
    op = op&input;      // This will just the 3 bits of interest from the actual input

    //shift the three bits to the 0
    return op>>start_bit;

}
void main(){
    uint32_t input=0x7337;
    int start_bit=7;
    uint32_t answer = grab_three_bits(input, start_bit);
    printf("%d\t %u",answer, answer);

}