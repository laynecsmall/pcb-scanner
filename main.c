#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "mux.h"
#include "uart.h"
#include "xbee.h"

uint8_t j,k = 0;

char char_buf1[30]; //buffers for UART operation
char char_buf2[30];
uint16_t mat_results[X_MAT_SIZE][Y_MAT_SIZE] = {{0}}; //results for the mat scan

uint8_t flags = 0; //flags register contains notices for main loop

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    XBEE_Initialize();
    MUX_initialize();
    TRISBbits.TRISB9 = 0; //need to set RB9 as gpio, not included in pin mgr
    
    INTCON2bits.GIE = 1; //enable global interrupts
    
    
    //set the baud rate for the uart modules
    U1BRG = calculate_UXBRG(BAUD);
    U2BRG = calculate_UXBRG(BAUD);
              
    while (1)
    {
        delay_s(2);
        LED_on();
        if (timerFlag){
            UART2_writeLine("Timer flag set\n");
        }
        else{
            UART2_writeLine("Timer flag NOT set \n");
        }
    }
    return -1;
}

void blink_led(void){
        //blink LED
    LED_on();
    delay_ms(500);                   
    LED_off();
    delay_ms(500);
}

uint16_t read_adc(void){
    PORTBbits.RB4 = 0; //toggle chip select. investigate framed mode later
    uint16_t adc = SPI2_Exchange16bit( SPI2_DUMMY_DATA );
    PORTBbits.RB4 = 1;
    return adc;
}














































/**
 End of File
*/