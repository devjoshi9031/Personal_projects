#include<stdio.h>

//This is to check if everything is already define or not. If not then define. Otherwise this can define multiple instance of the same variable.
#ifndef _HEADER_H_
#define _HEADER_H_

#define RED 18		//Macro for RED LIGHT PIN
#define G 19		//Macro for GREEN LIGHT PIN
#define B 1			//Macro for BLUE LIGHT PIN

#define TOUCH_OFFSET 550		// Initialization for touch pad.
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)	//To get the data from the slider


extern volatile int delay_array[5];		//array to hold the delay information.
/*
 * Function to initialize the LED pins and gating controls. It sets the data direction for the pins stes the pin for output.
 *
 */
void init_function(void);

/*
 * Function to turn the white LED ON. This will turn all the LED pins to high.
 */
void white_on(void);

/*
 * Function to turn the white LED OFF. This will turn all the GPIOX->PSOR to one.
 */
void white_off(void);

/*
 * Function to intialize the touch slider. Code adapted from the Github repository.
 */
void TOUCH_INIT(void);

/*
 * Function to get the data from the touch slider. According to the value of the touch scan it will also change the LED COLOR. This function will be called from the delay function and the infinite led function.
 */
void touch_scan(void);

/*
 * Delay function that incorporates a while loop and calls touch scan function to poll the slider every 100msec.
 */
void delay(volatile unsigned int, unsigned int);

/*
 * This is the function that incorporates the infinte loop to turn on and off the LEDs depending on the value of the slider.
 */
void infinite_led(void);

#endif
