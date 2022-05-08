#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

int servoPos;

void servoInit(void) {
  //Enabling the PWM generator (bit 36), PIOB already enablen for Tempsensor
  *AT91C_PMC_PCER1 = (0x10);
  
  //Let peripheral control the pin REG_PIOB_PDR
  *AT91C_PIOB_PDR = (0x20000);
  
  //Activate peripheral B to control the pin in REG_PIOB_ABSR
  *AT91C_PIOB_ABMR = (0x20000);
  
  //Enable PWM-channel in ENA_CHID1
  *AT91C_PWMC_ENA = (0x2);
  
  //Set Pre-scaler to Master_CLK/32 in PWM_CMRx
  *AT91C_PWMC_CH1_CMR = (0x5);
  
  //Write a value to PWM_CPRD (20ms)
  *AT91C_PWMC_CH1_CPRDR = (0xCD14);
  
  //Write a value to PWM_CDTY(1ms);
  *AT91C_PWMC_CH1_CDTYR = (4200);      //Neutral position?
  
  servoPos = (0 + (4200 - 2200) * (180 - 0) / (6000 - 2200));
  
}

//Skriva färdigt denna kanske?
void turnServo(int degree) {
  if(degree > 180) {
    degree = 180;
  }
  else if(degree <= 0) {
    degree = 0;
  }
  servoPos = degree;
  //Mapping: (newlow + (value - oldlow) * (newhigh - newlow) / (oldhigh - oldlow))
  degree = (2200 + (degree - 0) * (6000 - 2200) / (180 - 0));
  *AT91C_PWMC_CH1_CDTYUPDR = (degree);
}

//Tracka solen
void trackSun(void) {
  int key = 0;
  char ch[3];
  printTrackSun();
  while(key != 10) {
    key = readKey();
    
    measureLight();     //Hämta ljusinfo

    if(light[1] > (light[0]+500)) {
      turnServo(servoPos-5); 
    }
    else if(light[1] < (light[0]-100)){
      turnServo(servoPos+5);
    }
    else if(light[1] > (light[0]-5) || (light[0]-5) > light[0]){
      turnServo(servoPos); 
    }
    //Formatting
    write_data_2_display(0xA8);
    write_data_2_display(0x00);
    write_command_2_display(0x24);
    sprintf(ch, "%ld", servoPos);
    writeStringToDisplay(ch);
    if(servoPos < 100 && servoPos > 10) {
      write_data_2_display(0xAA);
      write_data_2_display(0x00);
      write_command_2_display(0x24);
      
      write_data_2_display(0x5F);
      write_data_2_display(0x00);
      write_command_2_display(0xC0);
    }
    else if(servoPos < 10) {
      write_data_2_display(0xAA);
      write_data_2_display(0x00);
      write_command_2_display(0x24);
      
      write_data_2_display(0x5F);
      write_data_2_display(0x00);
      write_command_2_display(0xC0);
      
      write_data_2_display(0xA9);
      write_data_2_display(0x00);
      write_command_2_display(0x24);
      
      write_data_2_display(0x5F);
      write_data_2_display(0x00);
      write_command_2_display(0xC0);
    }
    //End of formatting
  }
}

//Tweaka denna... delays
void servoSweep(void) {
  int i;
  for(i = 0; i <= 180; i++) {
    turnServo(i);
    delay(50);
  }
  for(i = 180; i >= 0; i--) {
    turnServo(i);
    delay(50);
  }
  turnServo(90);        //Resetting
}

/*
  Värden
  2200 - ca 0 grader
  4200 - 90 grader
  6000 - 180 grader
*/