/*
 * File:   uart.c
 * Author: Layne
 *
 * Created on December 1, 2016, 4:12 PM
 */


#include "xc.h"
#include <stdint.h>
#include "mcc_generated_files/mcc.h"


void UART1_readLine(char *target, uint8_t bufsize){
    uint8_t pos1 = 0;
    
    while(1){
        while (!UART1_DataReady){} //wait till data is ready
        if (pos1 > bufsize -2){ //if buffer is full, end
            break;
        }
        else{
            target[pos1++] = UART1_Read();
            if (target[pos1-1] == '\n'){
                break;
            }
        }
    }
    target[pos1++] = '\n';
    target[pos1] = '\0';
}

void UART2_readLine(char *target, uint8_t bufsize){
    uint8_t pos2 = 0;
    
    while(1){
        while (!UART2_DataReady){} //wait till data is ready
        if (pos2 > bufsize -2){ //if buffer is full, end
            break;
        }
        else{
            target[pos2++] = UART2_Read();
            if (target[pos2-1] == '\n'){
                break;
            }
        }
    }
    target[pos2++] = '\n';
    target[pos2] = '\0';
}

void UART1_writeLine(char *outString){
    while(*outString){
        UART1_Write(*outString++);
    }      
}

void UART2_writeLine(char *outString){
    while(*outString){
        UART2_Write(*outString++);
    }      
}