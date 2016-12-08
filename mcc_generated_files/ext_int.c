/**
  EXT_INT Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    ext_int.c

  @Summary
    This is the generated driver implementation file for the EXT_INT 
    driver using MPLAB(c) Code Configurator

  @Description:
    This source file provides implementations for driver APIs for EXT_INT. 
    Generation Information : 
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC24EP128MC206
        Driver Version    :  1.0
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.20
*/

/**
   Section: Includes
 */
#include <xc.h>
#include "ext_int.h"
#include "tmr1.h"


//***User Area Begin->code: Add External Interrupt handler specific headers 
#include "../main.h"
#include "../uart.h"
extern uint8_t flags;
//***User Area End->code: Add External Interrupt handler specific headers

/**
   Section: External Interrupt Handlers
 */
/**
  Interrupt Handler for EX_INT1 - INT1
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
{
    //***User Area Begin->code: External Interrupt 1***
    
    //start timer
    TMR1_SoftwareCounterClear(); //ensure counter is from zero
    clearTimerFlag(); //ensure timer flag has not yet started
//    TMR1_Start();
//    LED_off();
    
    //***User Area End->code: External Interrupt 1***
    EX_INT1_InterruptFlagClear();
}
/**
  Interrupt Handler for EX_INT2 - INT2
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT2Interrupt(void)
{
    //***User Area Begin->code: External Interrupt 2***
    TMR1_Stop();
    setTimerFlag() //timer has updated, indicate to main loop to check tmr value
    //***User Area End->code: External Interrupt 2***
    EX_INT2_InterruptFlagClear();
//    LED_off();
}
/**
  Interrupt Handler for EX_INT0 - INT1
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT0Interrupt(void)
{
    //***User Area Begin->code: External Interrupt 0***

    //***User Area End->code: External Interrupt 0***
    EX_INT0_InterruptFlagClear();
}
/**
    Section: External Interrupt Initializers
 */
/**
    void EXT_INT_Initialize(void)

    Initializer for the following external interrupts
    INT1
    INT2
    INT1
*/
void EXT_INT_Initialize(void)
{
    /*******
     * INT1
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT1_InterruptFlagClear();   
    EX_INT1_PositiveEdgeSet();
    EX_INT1_InterruptEnable();
    /*******
     * INT2
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT2_InterruptFlagClear();   
    EX_INT2_PositiveEdgeSet();
    EX_INT2_InterruptEnable();
    /*******
     * INT1
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT0_InterruptFlagClear();   
    EX_INT0_PositiveEdgeSet();
}
