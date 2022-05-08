#include <stdio.h>
#include <string.h>
#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

//Display Stuff
//Read status
unsigned char read_status_display(void) {
  unsigned char temp;
  
  // Setting databus as input ( pins 34-41, PIOC bits 2-9 )
  *AT91C_PIOC_ODR = (0x3FC);
  
  // Set dir as input ( pin 50, PIOC 13, high == input )
  *AT91C_PIOC_SODR = (1<<13);
  
  // Enable output for chip ( pin 51, PIOC 12, active low )
  *AT91C_PIOC_CODR = (1<<12);
  
  // Set C/D ( pin 46, PIOC 17 )
  *AT91C_PIOC_SODR = (1<<17);
  
  //Clear chip select diplay and read display ( pin 47, 48, PIOC 15,16, active low )
  *AT91C_PIOC_CODR = (0x18000);
  
  //Delay
  delay(40);
  
  //Read databus and save in temp ( db is pins 34-41, PIOC 2-9 )
  temp = *AT91C_PIOC_PDSR & (0x3FC);     //maskar fram relevanta bitar
  
  //Set chip select display and read display ( pin 47, 48, PIOC 15, 16, active low )
  *AT91C_PIOC_SODR = (0x18000);
    
  //Disable output for chip ( pin 51, PIOC 12, active low )
  *AT91C_PIOC_SODR = (1<<12);
  
  //Set dir as output ( pin 50, PIOC 13, low == output )
  *AT91C_PIOC_CODR = (1<<13);
  
  // Enable output for chip ( pin 51, PIOC 12, active low )
  *AT91C_PIOC_CODR = (1<<12);
  
  return temp;
}

//Write command
void write_command_2_display(unsigned char Command) {
      
    unsigned char command_data = Command;
    unsigned char status = 0x00;
    
    while(status != 0x0C) {
      status = read_status_display();
      status = status & 0x0C;
    }
  
    //Clear databus ( pins 34-41, PIOC bits 2-9 )
    *AT91C_PIOC_CODR = (0x3FC); 
    
    //write command to databus
    *AT91C_PIOC_SODR = (command_data<<2);
      
    //Set dir as output ( pin 50, PIOC 13, low == output )
    *AT91C_PIOC_CODR = (1<<13);
    
    // Enable output for chip ( pin 51, PIOC 12, active low )
    *AT91C_PIOC_CODR = (1<<12);
    
    // Enable output for databus ( pins 34-41 PIOC bits 2-9 )
    *AT91C_PIOC_OER = (0x3FC);
    
    //Set C/D to command ( pin 46, PIOC 17, command == high )
    *AT91C_PIOC_SODR = (1<<17);
    
    //Clear chip select display (pin 47, PIOC 16) 
    *AT91C_PIOC_CODR = (1<<16);
    
    //Clear write display (pin 49, PIOC 14)
    *AT91C_PIOC_CODR = (1<<14);
    
    //Delay
    delay(40);
    
    //Set chip enable display (pin 47, PIOC 16) 
    *AT91C_PIOC_SODR = (1<<16);
    
    //Set write display (pin 49, PIOC 14)
    *AT91C_PIOC_SODR = (1<<14);
    
    // Disable output for chip ( pin 51, PIOC 12, active low)
    *AT91C_PIOC_SODR = (1<<12);
    
    // Setting databus as input ( pins 34-41, PIOC bits 2-9 )
    *AT91C_PIOC_ODR = (0x3FC);
    
    return;
}

//Write data
void write_data_2_display(unsigned char Data) {
  
    unsigned char cmd_data = Data;
    unsigned char status = 0x00;
    
    while(status != 0x0C) {
      status = read_status_display();
      status = status & 0x0C;
    }
  
    //Clear databus dvs, skriv till CODR för rätt pinnar/PIO-enhet
    *AT91C_PIOC_CODR = (0x3FC); 
    
    //write data to databus
    *AT91C_PIOC_SODR = (cmd_data<<2);
    
    //Set dir as output ( pin 50, PIOC 13, low == output)
    *AT91C_PIOC_CODR = (1<<13);
    
    // Enable output for chip ( pin 51, PIOC 12, active low)
    *AT91C_PIOC_CODR = (1<<12);
    
    // Enable output for databus, pins 34-41 (PIOC bits 2-9)
    *AT91C_PIOC_OER = (0x3FC);
    
    //clear C/D = 0 for data ( pin 46, PIOC 17 )
    *AT91C_PIOC_CODR = (1<<17);
    
    //Clear chip select display (pin 47, PIOC 16) 
    *AT91C_PIOC_CODR = (1<<16);
    
    //Clear write display (pin 49, PIOC 14)
    *AT91C_PIOC_CODR = (1<<14);
    
    //Delay
    delay(40);
    
     //Set chip enable display (pin 47, PIOC 16) 
    *AT91C_PIOC_SODR = (1<<16);
    
    //Set write display (pin 49, PIOC 14)
    *AT91C_PIOC_SODR = (1<<14);
    
    // Disable output for chip ( pin 51, PIOC 12, active low)
    *AT91C_PIOC_SODR = (1<<12);
    
    // Setting pins as input
    // Databus are pins 34-41 (PIOC bits 2-9)
    *AT91C_PIOC_ODR = (0x3FC);
    
    return;
}

//Display Initialization
void init_display(void) {
  
  *AT91C_PIOC_PER = 0xFF3FC;  //Enable PC2-9 and PC12-19
  *AT91C_PIOC_OER = 0xFF000;
  *AT91C_PIOD_PER = 0x1;  //Enable PD0
  *AT91C_PIOD_OER = 0x1; //Enable otuput
  
  *AT91C_PIOD_CODR = 0x1; //Reset the screen
  delay(10000); //Delay

  //Set reset display ( pin 25, PIOD 0 )
  *AT91C_PIOD_SODR = (0x1);
  
  // Copy paste from instructions
  write_data_2_display(0x00);
  write_data_2_display(0x00);
  write_command_2_display(0x40);//Set text home address
  
  write_data_2_display(0x00);
  write_data_2_display(0x40);
  write_command_2_display(0x42); //Set graphic home address
  
  write_data_2_display(0x1e);
  write_data_2_display(0x00);
  write_command_2_display(0x41); // Set text area
  
  write_data_2_display(0x1e);
  write_data_2_display(0x00);
  write_command_2_display(0x43); // Set graphic area
  write_command_2_display(0x80); // text mode
  write_command_2_display(0x94); // Text on graphic off
}

void clearDisplay(void) {
  int i;
  //Set Adress Pointer (0x24) and Data 1 == 0x00, Data 2 == 0x00
  write_data_2_display(0x00);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
  
  for(i = 0; i < 640; i++) {
    write_data_2_display(0x00);
    write_command_2_display(0xC0);
  }
  //Set Adress Pointer (0x24) and Data 1 == 0x00, Data 2 == 0x00
  write_data_2_display(0x00);
  write_data_2_display(0x00);
  write_command_2_display(0x24);
}

void blinkCursor(void) {
  //Font selection
  write_data_2_display(0x03);
  write_data_2_display(0x00);
  write_command_2_display(0x70);
      
  write_data_2_display(0x45);
  write_command_2_display(0xC4);
    
  delay(10000000);   
    
  write_data_2_display(0x00);
  write_command_2_display(0xC4);
  
  delay(10000000);
  
  //Font reset
  write_data_2_display(0x02);
  write_data_2_display(0x00);
  write_command_2_display(0x70);
}

void writeCharToDisplay(char ch) {
  write_data_2_display(ch - 32);
  write_command_2_display(0xC0);
}

void writeStringToDisplay(char* str) {
  while(*str) {
    writeCharToDisplay(*str++);
  }
}