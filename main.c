#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "mux.h"

uint16_t adc = 0;
uint8_t j = 0;


char char_buf[30];

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TRISBbits.TRISB9 = 0; //need to set RB9 as gpio, not included in pin mgr
    U1BRG = FCY/(4*BAUD)-1;
    //U1BRG = 2401; //9600
    //U1BRG = 545;  //19200
    
    enable_in_mux();
    enable_out_mux();
    select_mux_line(0,0);
      
    while (1)
    {
        PORTBbits.RB9 = 1;
        
        //UART1_WriteBuffer("Reading:\r\n",7U);
        //__delay32(FCY*0.1);
        
        PORTBbits.RB4 = 0; //toggle chip select. investigate framed mode later
        uint16_t adc = SPI2_Exchange16bit( SPI2_DUMMY_DATA );
        PORTBbits.RB4 = 1;
       
        printf(char_buf, "%u\n", adc);
              
        //blink LED
        __delay32(FCY*0.5);                    
        PORTBbits.RB9 = 0;  
        __delay32(FCY*0.5);
        
    }

    return -1;
}


/**
 End of File
*/