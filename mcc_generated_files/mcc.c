/**
  @Generated MPLAB(c) Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC24EP128MC206
        Driver Version    :  1.02
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

// Configuration bits: selected in the GUI

// FICD
#pragma config ICS = PGD3    // ICD Communication Channel Select bits->Communicate on PGEC3 and PGED3
#pragma config JTAGEN = OFF    // JTAG Enable bit->JTAG is disabled

// FPOR
#pragma config ALTI2C1 = OFF    // Alternate I2C1 pins->I2C1 mapped to SDA1/SCL1 pins
#pragma config ALTI2C2 = OFF    // Alternate I2C2 pins->I2C2 mapped to SDA2/SCL2 pins
#pragma config WDTWIN = WIN25    // Watchdog Window Select bits->WDT Window is 25% of WDT period

// FWDT
#pragma config WDTPOST = PS32768    // Watchdog Timer Postscaler bits->1:32768
#pragma config WDTPRE = PR128    // Watchdog Timer Prescaler bit->1:128
#pragma config PLLKEN = ON    // PLL Lock Enable bit->Clock switch to PLL source will wait until the PLL lock signal is valid.
#pragma config WINDIS = OFF    // Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bit->Watchdog timer enabled/disabled by user software

// FOSC
#pragma config POSCMD = NONE    // Primary Oscillator Mode Select bits->Primary Oscillator disabled
#pragma config OSCIOFNC = OFF    // OSC2 Pin Function bit->OSC2 is clock output
#pragma config IOL1WAY = ON    // Peripheral pin select configuration->Allow only one reconfiguration
#pragma config FCKSM = CSDCMD    // Clock Switching Mode bits->Both Clock switching and Fail-safe Clock Monitor are disabled

// FOSCSEL
#pragma config FNOSC = FRCPLL    // Oscillator Source Selection->Fast RC Oscillator with divide-by-N with PLL module (FRCPLL)
#pragma config PWMLOCK = ON    // PWM Lock Enable bit->Certain PWM registers may only be written after key sequence
#pragma config IESO = ON    // Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FGS
#pragma config GWRP = OFF    // General Segment Write-Protect bit->General Segment may be written
#pragma config GCP = OFF    // General Segment Code-Protect bit->General Segment Code protect is Disabled

#include "mcc.h"

/**
 Section: Local Variables
*/

/**
* a private place to store the error code if we run into a severe error
*/

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    INTERRUPT_Initialize();
    UART2_Initialize();
    SPI2_Initialize();
    UART1_Initialize();
    CORCON_ModeOperatingSet(CORCON_MODE_PORVALUES);
}

void OSCILLATOR_Initialize(void)
{
    // CF no clock failure; NOSC FRCPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONL((uint8_t) (0x0100 & 0x00FF));
    // FRCDIV FRC/1; PLLPRE 5; DOZE 1:8; PLLPOST 1:2; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3003;
    // TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROON disabled; ROSEL disabled; RODIV Base clock value; ROSSLP disabled; 
    REFOCON = 0x0000;
    // PLLDIV 112; 
    PLLFBD = 0x0070;
    // RND disabled; SATB disabled; SATA disabled; ACCSAT disabled; 
	CORCONbits.RND = 0;
	CORCONbits.SATB = 0;
	CORCONbits.SATA = 0;
	CORCONbits.ACCSAT = 0;
    // WDTO disabled; TRAPR disabled; SLEEP disabled; BOR disabled; CM disabled; SWR disabled; SWDTEN disabled; EXTR disabled; POR disabled; VREGSF disabled; IDLE disabled; IOPUWR disabled; VREGS disabled; 
    RCON = 0x0000;
}

SYSTEM_RESET_TYPES SYSTEM_GetResetCause(void)
{
    const uint16_t rconcopy = RCON;
    uint16_t errorCode = 0;
    if (rconcopy & 0x8000) /* TRAPR */
    {
        errorCode = ERR_RCON_TRAPR;
    }
    else if (rconcopy & 0x4000) /* IOPUWR */
    {
        errorCode = ERR_RCON_IOPUWR;    
    }
    else if (rconcopy & 0x0200) /* CM */
    {
        errorCode = ERR_RCON_CM;    
    }
    else if (rconcopy & 0x0010) /* WDTO */
    {
        errorCode = ERR_RCON_WDTO_ISR;    
    }      
    return errorCode;
}
/**
 End of File
*/