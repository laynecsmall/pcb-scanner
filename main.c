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

#define FCY 92236800UL
#define BAUD 9600UL
#define delay_us(x) __delay32(((x*FCY)/1000000UL)) // delays x us
#define delay_ms(x) __delay32(((x*FCY)/1000UL))  // delays x ms

char char_buf[30];
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    U1BRG = FCY/(4*BAUD)-1;

    while (1)
    {
        // Add your application code
        PORTBbits.RB9 = 1;
        //UART1_WriteBuffer("Reading:\r\n",7U);
        //__delay32(FCY*0.1);
        PORTAbits.RA0 = 0;
        PORTBbits.RB4 = 0;
        uint16_t adc = SPI2_Exchange16bit( SPI2_DUMMY_DATA );
        PORTBbits.RB4 = 1;
        PORTAbits.RA0 = 1;
        sprintf(char_buf, "Read: %d\r\n", adc);
        UART1_WriteBuffer(char_buf,sizeof(char_buf)+2);
        __delay32(FCY*0.1);
                      
        PORTBbits.RB9 = 0;
    }

    return -1;
}
/**
 End of File
*/