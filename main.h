/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAIN
#define	MAIN

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>
#include <libpic30.h>
#include <stdint.h>
#include "mux.h"

#define FCY 41856001UL
#define BAUD 9600UL

#define X_MAT_SIZE 14U
#define Y_MAT_SIZE 14U

#define delay_us(x) __delay32(x*(FCY/1000000UL)) // delays x us
#define delay_ms(x) __delay32(x*(FCY/1000UL))  // delays x ms
#define delay_s(x) __delay32(x*FCY)  // delays x ms
#define setBit(reg, bit, val)    reg = val ? reg | (1 << bit) : reg & ~(1 << bit);
#define getBit(a,b) ((a) & (1<<(b)))

/*
 * Flag map:
 * =========================
 * | Bit  | Flag
 * |------|-----------------
 * | 0    | UART_update
 * | 1    | Timer
 * | 2    | Mat scan
 * | 3    |
 * | 4    |
 * | 5    |
 * | 6    | 
 * | 7    |
 * =========================
 */

//define useful flags
//uart
#define setUartFlag() setBit(flags,0,1);
#define clearUartFlag() setBit(flags,0,0);
#define uartFlag getBit(flags,0)

//timer
#define setTimerFlag() setBit(flags,1,1);
#define clearTimerFlag() setBit(flags,1,0);
#define timerFlag getBit(flags,1)

//Mat scan
#define setMatScanFlag() setBit(flags,2,1);
#define clearMatScanFlag() setBit(flags,2,0);
#define matScanFlag getBit(flags,2)

#define calculate_UXBRG(a) FCY/(4*a)-1
#define LED_on() PORTBbits.RB9 = 1
#define LED_off() PORTBbits.RB9 = 0

void blink_led(void);
uint16_t read_adc(void);

#endif	/* MAIN */

