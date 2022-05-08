#include <stdio.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

void printMainMenu(void) {
  //Main Menu
  write_data_2_display(0x0A);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Main Menu");

  //Line 1
  write_data_2_display(0x78);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("1. Track sun");
  
  //Line 2
  write_data_2_display(0xB4);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("2. Display data");
  
  //Line 3
  write_data_2_display(0xF0);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("3. Settings");
  
  //Line 4
  write_data_2_display(0x2C);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("4. \"Fast Mode\"");
}

void printTrackSun(void){
  char ch[3];
  //Tracking sun
  write_data_2_display(0x09);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Tracking sun");
  
  //position of servo
  write_data_2_display(0x9F);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Degrees: ");
  
  write_data_2_display(0xA8);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  sprintf(ch, "%ld", servoPos);
  writeStringToDisplay(ch);
  //Begin formatting
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
  
  //* to exit
  write_data_2_display(0xC2);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("* to exit");
  
}

void printSettingsMenu(void) {
  //Settings Menu
  write_data_2_display(0x0B);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Settings");
  
  //Line 1
  write_data_2_display(0x78);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("1. Set alarm");
  
  //Line 2
  write_data_2_display(0xB4);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("2. Reset servo");
  
  //Line 3
  write_data_2_display(0xF0);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("3. Trigger \"Disco mode\"");
  
  //* to exit
  write_data_2_display(0xC2);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("* to exit");
}

//Display Data
void printDisplayDataMenu(void) {
  //Display Data
  write_data_2_display(0x09);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Display data");
  
  //Average Temp
  write_data_2_display(0x78);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("1. Average temperature");
  
  //Max Temp
  write_data_2_display(0xB4);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("2. Max temperature");
  
  //Min Temp
  write_data_2_display(0xF0);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("3. Minimum temperature");

  //* to exit
  write_data_2_display(0xC2);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("* to exit");
}

void printAlarmMenu(void) {
  //Set alarm
  write_data_2_display(0x09);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Set Alarm");
  
  //Upper Value
  write_data_2_display(0x78);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Upper Value: ");
  
  //Lower Value
  write_data_2_display(0xF0);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Lower Value: ");
  
  //* to exit
  write_data_2_display(0xC2);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("* to exit");
}