#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

int fastMode = 0;

//Delay
void delay(int val) {
  int i;
  for(i = 0; i < val; i++)
    asm("nop");
}


int main()
{
  SystemInit();
  *AT91C_PMC_PCER = (0x2000); // Start PIOC clock
  *AT91C_PMC_PCER = (0x4000); // Start PIOD clock
  initKeypadPins();
  init_display();
  initTempSensor();
  initLightSensor();
  servoInit();
  initDatabase();
  clearDisplay();

  SysTick_Config(1500000);

  while(1) {
    printMainMenu();
    checkAlarm();
    checkFastMode();
    switch(keyDebouncer()) {
      case 1:
        //Track sun
        clearDisplay();
        trackSun();
        break;
      case 2:
        //Display data
        clearDisplay();
        fastMode = 0;
        displayData();
        break;
      case 3:
        //Settings
        clearDisplay();
        systemSettings();
        break;
      case 4:
        //Testo mode
        startFastMode();
        break;
      default:
        break;
    }
    clearDisplay();
  }
}

void checkFastMode(void) {  
  if(fastMode == 1) {
    //Fast Mode active
    write_data_2_display(0x92);
    write_data_2_display(0x01);
    write_command_2_display(0x24);
    writeStringToDisplay("Fast Mode: ACTIVE");
  }
  else {
    //Fast mode inactive
    write_data_2_display(0x90);
    write_data_2_display(0x01);
    write_command_2_display(0x24);
    writeStringToDisplay("Fast Mode: INACTIVE");
  }
}

void startFastMode(void) {
  if(fastMode == 1) {
    fastMode = 0;
  }
  else {
    fastMode = 1;
  }
}