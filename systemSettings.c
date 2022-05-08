#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"
#include "stdio.h"

int alarmUpper;
int alarmLower;
int disco = 0;

void systemSettings(void) {
  int key = 0;
  while(key != 10) {
    printSettingsMenu();
    key = keyDebouncer();
    switch(key) {
      case 1:
        //Set alarm
        clearDisplay();
        printAlarmMenu();
        setAlarm();
        clearDisplay();
        break;
      case 2:
        //Reset servo
        turnServo(90);
        break;
      case 3:
        if(disco == 0) {
          write_command_2_display(0x84);
          disco = 1;
        }
        else {
          write_data_2_display(0x1e);
          write_data_2_display(0x00);
          write_command_2_display(0x80);
          disco = 0;
        }
        break;
      default:
        break;
    }
    clearDisplay();
  }
}

void setAlarm(void) {
  int temp[4];
  //Läs in 2 siffror
  temp[0] = keyDebouncer();
  write_data_2_display(0x85);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  if(temp[0] == 11) {
    writeCharToDisplay('0');
    temp[0] = 0;
  }
  else {
    writeCharToDisplay(temp[0] + '0');
  }
  
  temp[1] = keyDebouncer();
  if(temp[1] == 11) {
    writeCharToDisplay('0');
    temp[1] = 0;
  }
  else {
    writeCharToDisplay(temp[1] + '0');
  }
  
  //Läs in 2 siffror till
  temp[2] = keyDebouncer();
  write_data_2_display(0xFD);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  if(temp[2] == 11) {
    writeCharToDisplay('0');
    temp[2] = 0;
  }
  else {
    writeCharToDisplay(temp[2] + '0');
  }
  
  temp[3] = keyDebouncer();
  if(temp[3] == 11) {
    writeCharToDisplay('0');
    temp[3] = 0;
  }
  else {
    writeCharToDisplay(temp[3] + '0');
  }
  
  //Siffra 1*10 + siffra 2 == upper
  alarmUpper = temp[0]*10 + temp[1];

  //Siffra 3*10 + siffra 4 == lower
  alarmLower = temp[2]*10 + temp[3];
  //printf("alarmUpper = %d \n alarmLower = %d\n", alarmUpper, alarmLower);
  
  //Vänta på * knapp
  while(keyDebouncer() != 10){}
}

void checkAlarm(void) {
  while(tempflag != 1) {
    measureTemp();
  }
  tempflag = 0;
  
  if(temperature > alarmLower && temperature < alarmUpper) {
    //Inside range of alarm
    write_data_2_display(0xAC);
    write_data_2_display(0x01);
    write_command_2_display(0x24);
    writeStringToDisplay("Alarm status: CAUTION");
  }
  else {
    //Outside range
    write_data_2_display(0xAD);
    write_data_2_display(0x01);
    write_command_2_display(0x24);
    writeStringToDisplay("Alarm status: ACTIVE");
  }
}