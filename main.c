#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "mux.h"
#include "uart.h"

uint8_t j = 0;

char char_buf1[30];
char char_buf2[30];

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TRISBbits.TRISB9 = 0; //need to set RB9 as gpio, not included in pin mgr
    U1BRG = FCY/(4*BAUD)-1;
    U2BRG = FCY/(4*9600UL)-1;
    //U1BRG = 2401; //9600
    //U1BRG = 545;  //19200
    
    enable_in_mux();
    enable_out_mux();
    select_mux_line(0,0);
    
    PORTBbits.RB15 = 0; //XBee sleep
    PORTBbits.RB12 = 1; //XBee reset
          
    while (1)
    {
        blink_led();
//        UART1_writeLine("Ready\n");
//        __delay32(FCY*2);
//        UART1_writeLine("Begin:\n");
//        
//        //enter command mode, return the response
////        
        UART1_writeLine("Beginning serial attempt\n");
        
        UART2_writeLine("+++");
        UART2_readLine(char_buf1, 3);
        UART1_writeLine(char_buf1);
        UART1_writeLine("End serial attempt, waiting 3 seconds\n");
//        __delay32(FCY*1);
 
//        //get the node identifier
//        __delay32(FCY*0.5);
//        UART2_writeLine("ATMY\n");
//        UART2_readline(char_buf2, 30);
//        UART1_writeLine(char_buf2);
        
//        sprintf(char_buf1, "%u\n", read_adc());
//        UART1_writeLine(char_buf1);
//        blink_led();
    }
    return -1;
}

void blink_led(void){
        //blink LED
    PORTBbits.RB9 = 1;
     __delay32(FCY*0.5);                    
     PORTBbits.RB9 = 0;  
     __delay32(FCY*0.5);   
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