/*
 * Author: Dev Joshi {devjoshi9031@gmail.com}
 * PURPOSE: Personal Project
 * @brief: Some of the code adapted from Dean's Github repository for NXP FRDM 25z.
 *
 */



#include<stdio.h>
#include "header.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


volatile int delay_array[5] = {5,10,20,30,0};

void init_function(void){
	// Initialization of PORT B [RED LIGHT], PORTB [Green LIGHT], and PORTC [BLUE LIGHT] .
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
    // Setting the port control register for port B and D
    PORTB->PCR[RED] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[G] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED] |= PORT_PCR_MUX(1);
    PORTB->PCR[G] |= PORT_PCR_MUX(1);
    GPIOB->PDDR |= (1<<RED) | (1<<G);					// Setting the direction of the pins to be output.
    // Setting the port control register for port D.
    PORTD->PCR[B] &= ~PORT_PCR_MUX_MASK;
    PORTD->PCR[B] |= PORT_PCR_MUX(1);
    GPIOD->PDDR |= (1<<B);							// Setting the direction og the pins to be output.
    GPIOD->PSOR |= (1<<B);							//initally the LEDs will be off.
    GPIOB->PSOR |= (1<<RED) | (1<<G);
}

void white_on(void){
	GPIOB->PCOR |= (1<<RED) | (1<<G);
	GPIOD->PCOR |= (1<<B);
}

void white_off(void){
	GPIOB->PSOR |= (1<<RED) | (1<<G);
	GPIOD->PSOR |= (1<<B);
}


void TOUCH_INIT(void){
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;
	TSI0->GENCS = TSI_GENCS_MODE(0u)|
	TSI_GENCS_REFCHRG(0u) |
	TSI_GENCS_DVOLT(0u) |
	TSI_GENCS_EXTCHRG(0u) |
	TSI_GENCS_PS(0u) |
	TSI_GENCS_NSCN(31u) |
	TSI_GENCS_TSIEN_MASK |
	TSI_GENCS_EOSF_MASK;
}

void touch_scan(void){
	unsigned int touch_val=0;
	TSI0->DATA = TSI_DATA_TSICH(10u);
	TSI0->DATA |= TSI_DATA_SWTS_MASK;
	while(!(TSI0->GENCS & TSI_GENCS_EOSF_MASK))
		;
	touch_val = TOUCH_DATA-TOUCH_OFFSET;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK;

//	printf("value: %d\n",touch_val);
	// IF this is the initial phase of the infinite loop. It will turn on and off the white LED.
	if(touch_val>=75 && touch_val<=85 && delay_array[4]==0){
		white_off();
		white_on();
	}
	// Once the slider is been touched it will change the color from WHITE TO RED.
	else if(touch_val >= 75 && touch_val<=150){
		delay_array[4]=1;
		white_off();
		GPIOB->PCOR |= (1<<RED);
	}
	// Once the slider is been touched it will change the color from WHITE TO GREEN.
	else if(touch_val>150 && touch_val<= 250){
		delay_array[4]=1;
		white_off();
		GPIOB->PCOR |= (1<<G);

	}
	// Once the slider is been touched it will change the color from WHITE TO BLUE.
	else if(touch_val>250){
		delay_array[4]=1;
		white_off();
		GPIOD->PCOR |= (1<<B);
	}
	return;
}


void delay(volatile unsigned int num,unsigned int option){
	int initial_delay;
	// num will define how many times the for loop will run. If the value is 5, that means the delay will be 500ms. For each iteration of for loop the delay will be 100ms.
	for(int i=0;i<num;i++){
		initial_delay = 500000;
		while(initial_delay){
			__asm volatile ("nop");
			initial_delay--;
		}
		//depending if the delay is after turning ON or OFF a LED, it will call the touch_scan function every 100msec.
		if(option==1){
		touch_scan();
		}
	}

}




void infinite_led(void){
	//This is for the initial sequence defined before infinite loop.
	GPIOB->PCOR |= (1<<RED);							// RED ON
    delay(5,0);
    white_off();							// RED OFF
    delay(1,0);

	GPIOB->PCOR |= (1<<G);
    delay(5,0);
    white_off();
    delay(1,0);

	GPIOD->PCOR |= (1<<B);
    delay(5,0);
    white_off();
    delay(1,0);
    // The infinite loop that was mentioned in the assignment.
	while(1){
		for(int i=0;i<4;i++){
				touch_scan();
				delay(delay_array[i],1);
				white_off();
				delay(delay_array[0],0);
		}
	}
}


