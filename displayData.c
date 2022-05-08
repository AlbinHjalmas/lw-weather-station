#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>

void displayData(void) {
  int key = 0;
  while(key != 10) {
    printDisplayDataMenu();
    key = keyDebouncer();
    switch(key) {
      case 1:
        //Average Temperature
        clearDisplay();
        calculateAverage();
        break;
      case 2:
        //Max Temperature
        clearDisplay();
        calculateMax();
        break;
      case 3:
        //Min Temperature
        clearDisplay();
        calculateMin();
        break;
      default:
        break;
    }
    clearDisplay();
  }
}

void calculateAverage(void){
  int average[7] = {0};
  char ch[2];
  int c = 1;
  
  //Average
  write_data_2_display(0x0B);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Average");
  
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 1440; j++){
      if(database[i][j] == 0) {
        break;
      }
      average[i] = database[i][j] + average[i];
      c++;
    }
    average[i]= average[i]/c;
    
    //write average number per day
    write_data_2_display(182 + i*4);
    write_data_2_display(0x00);
    write_command_2_display(0x24);
    sprintf(ch, "%ld", average[i]);
    writeStringToDisplay(ch);
    
    //write d + number of day
    write_data_2_display(152 + i*4);
    write_data_2_display(0x00);
    write_command_2_display(0x24);
    writeStringToDisplay("D");
    writeCharToDisplay((i + 1) + '0');
  }
  
  //* to exit
  write_data_2_display(0xC2);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("* to exit");
  
  while(keyDebouncer() != 10){} 
  
}

void calculateMax(void){
  char ch[2];
  
  //Max
  write_data_2_display(0x0D);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Max");
  
  for(int i = 0; i < 7; i++){
    //write max number per day
    write_data_2_display(182 + i*4);
    write_data_2_display(0x00);
    write_command_2_display(0x24);
    sprintf(ch, "%ld", max[i]);
    writeStringToDisplay(ch);
    
    //write d + number of day
    write_data_2_display(152 + i*4);
    write_data_2_display(0x00);
    write_command_2_display(0x24);
    writeStringToDisplay("D");
    writeCharToDisplay((i + 1) + '0');
  }
  
  //* to exit
  write_data_2_display(0xC2);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("* to exit");
  
  while(keyDebouncer() != 10){} 
  
}

void calculateMin(void){
  char ch[2];
  
  //Min
  write_data_2_display(0x0D);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  writeStringToDisplay("Min");
  
  for(int i = 0; i < 7; i++){    
    //write min number per day
    write_data_2_display(182 + i*4);
    write_data_2_display(0x00);
    write_command_2_display(0x24);
    sprintf(ch, "%ld", min[i]);
    writeStringToDisplay(ch);
    
    //write d + number of day
    write_data_2_display(152 + i*4);
    write_data_2_display(0x00);
    write_command_2_display(0x24);
    writeStringToDisplay("D");
    writeCharToDisplay((i + 1) + '0');
  }
  
  //* to exit
  write_data_2_display(0xC2);
  write_data_2_display(0x01);
  write_command_2_display(0x24);
  writeStringToDisplay("* to exit");
  
  while(keyDebouncer() != 10){} 
  
}