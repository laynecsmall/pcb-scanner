#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "mux.h"
#include "uart.h"
#include "xbee.h"
#include "scanner_fit.h"

#define NUM_PARS 5
#define MAX_RESULTS 196

uint8_t j,k = 0;

char char_buf1[30]; //buffers for UART operation
char char_buf2[30];
//uint16_t mat_results[MAX_SAMPLES][X_MAT_SIZE][Y_MAT_SIZE] = {{{0}}}; //results for the mat scan
unsigned long int mat_results[MAX_RESULTS];
unsigned long int fit_base_values[MAX_RESULTS];
float fit_error[MAX_RESULTS];

mp_result *result;
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
    
    //initialize the matt base values
    for (j = 0; j < MAX_RESULTS; j++) fit_base_values[j] = j + 1;
    for (j = 0; j < MAX_RESULTS; j++) fit_error[j] = CONST_ERR;
    
    double p[5] = {1,1,1,1,1};//initial parameters for curve fitting
    double *pars = p;
    
    UART2_writeLine("Ready to begin\n");
    delay_s(2);
    
    
    select_mux_line(0,0);
    LED_on();
    
    
    while (1)
    {
        delay_s(1);
//        for (j = 0; j < X_MAT_SIZE; j++){
//            for (k = 0; k < Y_MAT_SIZE; k++){
//                mat_results[0][j][k] = read_adc();
//            }
//        }
        for (j = 0; j < 196; j++){
            mat_results[j] = read_adc();
        }
        
        find_fit(fit_base_values, 
                mat_results, 
                fit_error, 
                &result, 
                &pars, 
                MAX_RESULTS);
        
        UART2_writeLine("===============\n");
        for (j = 0; j < 196; j++){
//            for (k = 0; k < Y_MAT_SIZE; k++){
            sprintf(char_buf1, "%lu ", mat_results[j]);
            UART2_writeLine(char_buf1);
            delay_ms(5);
        }
            UART2_writeLine("\n");
        UART2_writeLine("---------------\n");
        
        for (j = 4; j < 5; j--){
            sprintf(char_buf1, "p%d: %f ",j, p[j]);
            UART2_writeLine(char_buf1);
            delay_ms(5);
        }
        UART2_writeLine("\n");
        
        


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