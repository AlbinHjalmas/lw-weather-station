#include "system_sam3x.h"
#include "at91sam3x8.h"
#include "interface.h"

int database[7][1440];
int min[7] = {100,100,100,100,100,100,100};
int max[7] = {-100,-100,-100,-100,-100,-100,-100};
int day = 0;
int minute = 0;
long clock = 0;

void initDatabase(void) {
  resetDatabase();
}

void SysTick_Handler(void) {
  clock++;
  measureTemp();
  if(fastMode == 1 && clock >= 60) {
    manageData();
    clock = 0;
  }
  else if((fastMode == 0) && clock >= (60*60)) {
    manageData();
    clock = 0;
  }
}

void manageData(void) {
  if(tempflag != 1)
     return;

  tempflag = 0;
  database[day][minute] = temperature;
  if(temperature < min[day]) {
    min[day] = temperature;
  }
  if(temperature > max[day]) {
    max[day] = temperature;
  }
  minute++;
  if(minute >= 1439 && day >= 6) {
    resetDatabase();
  }
  if(minute >= 1439) {
    day++;
    minute = 0;
  }
}

void resetDatabase(void) {
  int i;
  for(i = 0; i < 1439; i++) {
    database[0][i] = 0;
    database[1][i] = 0;
    database[2][i] = 0;
    database[3][i] = 0;
    database[4][i] = 0;
    database[5][i] = 0;
    database[6][i] = 0;
  }
  day = 0;
  minute = 0;
}