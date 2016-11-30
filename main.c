/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC24EP128MC206
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <xc.h>
#include <libpic30.h>

#include "scanner_uart.h"

#define FCY 41856001UL
#define BAUD 19200UL
#define delay_us(x) __delay32(((x*FCY)/1000000UL)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000UL))  // delays x ms

uint16_t adc = 0;
uint8_t ret = 0;

char char_buf[30];
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TRISBbits.TRISB9 = 0; //need to set RB9 as gpio, not included in pin mgr
    U1BRG = FCY/(4*BAUD)-1;
    //U1BRG = 2401; //9600
    //U1BRG = 545;  //19200
    
    while (1)
    {
        // Add your application code
        PORTBbits.RB9 = 1;
        LATBbits.LATB9 = 1;
        //UART1_WriteBuffer("Reading:\r\n",7U);
        //__delay32(FCY*0.1);
        
        PORTBbits.RB4 = 0; //toggle chip select. investigate framed mode later
        uint16_t adc = SPI2_Exchange16bit( SPI2_DUMMY_DATA );
        PORTBbits.RB4 = 1;
       
        sprintf(char_buf, "%u\n", adc);
        //sprintf(char_buf, "%u\n", U1BRG);
        ret = printf(char_buf,sizeof(char_buf));
        
        __delay32(FCY*1);
                      
        PORTBbits.RB9 = 0;
        LATBbits.LATB9 = 0;
        __delay32(FCY*1);
    }

    return -1;
}
/**
 End of File
*/