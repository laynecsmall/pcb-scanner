/*
 * File:   mux.c
 * Author: Layne
 *
 * Created on December 1, 2016, 12:14 PM
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include "main.h"
#include "mux.h"


// Used to select which input mux pin is connected to the ADC
// and which output mux line is connected to VCC
// 
// should have enable_in_mux() and enable_out_mux() called before using.

int i = 0;
uint8_t test = 2;

void select_mux_line(uint8_t in_pin, uint8_t out_pin){
    /*
     * micro to out_mux pin map:
     * RB8 -> MuxOut S0
     * RB7 -> MuxOut S1
     * RB4 -> MuxOut S2
     * RB5 -> MuxOut S3
     */
    
    /*
     * micro to in_mux pin map:
     * RB3 -> MuxIn S0
     * RB2 -> MuxIn S1
     * RG7 -> MuxIn S2
     * RG8 -> MuxIn S3
     */
   
    //bit lookup tables
    int port_b_out_map[4] = {8, 7, 5, 6};
    int in_map[4] = {3, 2,7,8};
    
    //get current port state
    long int b_temp = PORTB;
    long int g_temp = PORTG;
    
    //set relevant bits output mux
    for (i = 0; i < 4; i++){
        int lsb = getBit(out_pin,i);
        setBit(b_temp, port_b_out_map[i], lsb);
    }
    
    //set relevant bits for input mux
    //set first two bits of sel lines, on port B
    for (i = 0; i < 2; i++){
        int lsb = getBit(in_pin,i);
        setBit(b_temp, in_map[i], lsb);
    }
    //set second two bits of sel lines, on port G
    for (i = 2; i < 4; i++){
        int lsb = getBit(in_pin,i);
        setBit(g_temp, in_map[i], lsb);
    }
    
    //write changes to ports
    PORTB = b_temp;
    PORTG = g_temp;
}


void enable_out_mux(void){
    PORTDbits.RD8 = 0;
}

void disable_out_mux(void){
    PORTDbits.RD8 = 1;
}

void enable_in_mux(void){
    PORTGbits.RG6 = 0;
}

void disable_in_mux(void){
    PORTGbits.RG6 = 1;
}


