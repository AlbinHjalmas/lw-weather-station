#include <stdio.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

float temperature;
int tempflag;

float HandlerTemp;

//Initiating temp. sensor
void initTempSensor(void) {
  
  *AT91C_PMC_PCER = (0x8001000); // Start PIOB clock and TC0 clock
  
  //select Timer_clock1 as TCCLK
  *AT91C_TC0_CMR = (0xFFFFFFF8) & *AT91C_TC0_CMR;

  //enable counter and make a sw_reset
  *AT91C_TC0_CCR = (0x5);
  
  //Load counter to A when falling edge
  //Load counter to B when rising edge
  *AT91C_TC0_CMR = (0x60000) | *AT91C_TC0_CMR;
  
  //Enable pin ( pin 2, PIOB 25 )
  *AT91C_PIOB_PER = (0x2000000);
  
  //Enable the interrupt
  NVIC_ClearPendingIRQ(TC0_IRQn);
  NVIC_SetPriority(TC0_IRQn, 1);
  NVIC_EnableIRQ(TC0_IRQn);
}

//Returning temp. in Celsius
void measureTemp(void) {
  *AT91C_TC0_IER = (0x40);
  *AT91C_PIOB_OER = (1<<25);
  *AT91C_PIOB_CODR = (1<<25);
  delay(840000);
  *AT91C_PIOB_SODR = (1<<25);
  delay(420000);
  
  //startpulse
  *AT91C_PIOB_CODR = (1<<25);     // Disable before startpulse
  
  delay(210);
    
  *AT91C_PIOB_SODR = (1<<25);

  *AT91C_PIOB_ODR = (1<<25);      // Disable output tempsensor
   
  delay(25);
   
  *AT91C_TC0_CCR = (0x4);         // reset timer clock
}

//Interrup Handler for timer
void TC0_Handler(void) {
    *AT91C_TC0_IDR = (1<<6);
    double counterA = *AT91C_TC0_RA;
    double counterB = *AT91C_TC0_RB;
    HandlerTemp = counterB - counterA;
    temperature = ((HandlerTemp/210) - 273.15);
    tempflag = 1;
}