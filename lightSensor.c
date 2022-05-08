#include <stdio.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

int light[2];

void initLightSensor(void) {
  //PMC
  *AT91C_PMC_PCER1 = (0x20);    // Enabling the ADC
  *AT91C_PMC_PCER = (0x800);    // Enabling PIOA
  //Enable pins ( pins A5-6, PIOA bits 3-4 )
  *AT91C_PIOA_PER = (0x18);
  //Prescaler
  *AT91C_ADCC_MR = (1<<9);
  
}

void measureLight(void) {
  int status;
  
  status = (*AT91C_ADCC_SR) & (0x1000000);
  
  //Ch1
  *AT91C_ADCC_CHER = (0x2);
  
  //Start ADC
  *AT91C_ADCC_CR = (0x2);
  
  //Ch2
  *AT91C_ADCC_CHER = (0x4);
  
  //Start ADC
  *AT91C_ADCC_CR = (0x2);
  
  //Wait until conversion is done
  while(status != (0x1000000)){
    status = (*AT91C_ADCC_SR) & (0x1000000);
  }
  //Read value in ADC
  light[0] = *AT91C_ADCC_CDR1 & 0xFFF;
  light[1] = (*AT91C_ADCC_CDR2 & 0xFFF);       // +1100 to get a better value
    
  //Val 2 är mot skärmen
  //printf("\n Val 1:  %d \n", light[0]);
  //printf("\n Val 2: %d \n", light[1]);
}