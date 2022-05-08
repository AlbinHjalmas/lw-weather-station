#include <stdio.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

//Keypad Initialization
void initKeypadPins(void) {
  *AT91C_PIOD_ODSR=(1<<2);
  *AT91C_PIOD_PER=(1<<3); // Enable chip
  *AT91C_PIOC_PER=(0x03BC); // 2<<9
  *AT91C_PIOD_OER=(1<<2); //1<<2
  *AT91C_PIOC_SODR=(0x0380);
  *AT91C_PIOC_PPUDR=(0x0380);
}

//Keypad function
int readKey(void) {
  int column[3] = {256, 512, 128};
  int row[4] = {32, 4, 8, 16};
  int i, k, temp;
  int value = 0;
  
  *AT91C_PIOC_PER=(0x03BC); // 2<<9
  *AT91C_PIOD_OER=(1<<2); //1<<2
  *AT91C_PIOC_OER=(0x0380); // Enable output for columns
  
  *AT91C_PIOD_CODR=(1<<2); 
  *AT91C_PIOC_OER=(0x380);
  
  for(i = 0; i < 3; i++) {
    *AT91C_PIOC_CODR = column[i];
    for(k = 0; k < 4; k++) {
      //temp = *AT91C_PIOC_PDSR & row[k]; //Maska ut bit 2-5
      temp = *AT91C_PIOC_PDSR & (0x3c);
      if((temp&row[k]) == 0){
        value = ((k*3)+(i+1));
        break;
      }
    }
    *AT91C_PIOC_SODR = (0x380);
  }
  *AT91C_PIOC_ODR = (0x0380);
  delay(1300000);       //1 300 000
  return value;
}

int keyDebouncer(void) {
  int keyVal = 0;
  while(keyVal == 0) {
    keyVal = readKey();
  }
  while(readKey() != 0) {}
  delay(20);
  return keyVal;
}

