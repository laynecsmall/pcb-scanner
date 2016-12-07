/*
 * File:   xbee.c
 * Author: Layne
 *
 * Created on 5 December 2016, 9:28 AM
 */


#include "xc.h"
#include "main.h"

void XBEE_Initialize(void){
    PORTBbits.RB15 = 0; //XBee sleep pin low, no sleep
    PORTBbits.RB12 = 1; //XBee reset pin high, not reset
}

//pull the reset pin low for 500ms to reset the xbee
void XBEE_reset(void){
    PORTBbits.RB12 = 0;
    delay_ms(500);
    PORTBbits.RB12 = 1;
}

//TODO: investigate if need settings on xbee first in order to sleep
void XBEE_sleeep(void){
    PORTBbits.RB15 = 1;
}

void XBEE_wake(void){
    PORTBbits.RB15 = 0;
}