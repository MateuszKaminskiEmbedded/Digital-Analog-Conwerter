#include <xc.h>
#include <stdio.h>
#include "DeviceConfig.h"
#include "UART.h"
#include "delay.h"

void DAC_Init(unsigned int val){
    DAC1CON = 0x0;              // DAC disable
    DAC1CONbits.DACOE = 1;      // Output is enabled; CDAC voltage is connected to the pin
    DAC1CONbits.REFSEL = 3;    // Positive reference voltage = AVDD
    DAC1CONbits.DACDAT = val;   // Data input register bits for the CDAC
    DAC1CONbits.ON = 1;         // The CDAC is enabled
}

void main(){
	// Set ports as digital
    ANSELA = 1;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;

    TRISEbits.TRISE15 = 0;  // signal output UART
    
    //DAC1
    TRISAbits.TRISA4 = 0;
    
    // Set up PPS for UART 5
	U5RXR = 0b1100; // RF0 = U5RX
	RPE15R = 0b01011; // RC9 = U5TX

	Set_MaxSpeed_Mode();
	UART_Init();
    DAC_Init(0xFFF);
    
	while (1){
        for(int i = 0; i<0xFFF; i++){
            DAC1CONbits.DACDAT = i;
            delay_ms(1);
        }
    }
}

